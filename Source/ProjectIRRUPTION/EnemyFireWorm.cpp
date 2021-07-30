// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyFireWorm.h"

#include "BrainComponent.h"
#include "EnemyFireWormAIController.h"
#include "PaperFlipbookComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

AEnemyFireWorm::AEnemyFireWorm()
{
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollisionComponent"));

	BoxComponent->SetupAttachment(GetRootComponent());
	
	GetSprite()->SetRelativeLocationAndRotation(FVector(0.0, 0.0, 10.0), FQuat(FRotator(0.0, -90.0, 0.0)));
	BoxComponent->SetRelativeLocation(FVector(0.0, 0.0, 10.0));
	
	GetCapsuleComponent()->SetCapsuleHalfHeight(10.0);
	GetCapsuleComponent()->SetCapsuleRadius(10.0);
	BoxComponent->SetBoxExtent(FVector(3.0, 21.0, 13.0));

	BoxComponent->SetCollisionResponseToChannels(ECollisionResponse::ECR_Overlap);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
	BoxComponent->SetCollisionObjectType(ECollisionChannel::ECC_Pawn);
	
	GetCharacterMovement()->MaxWalkSpeed = 50.0f;

	this->Tags.Add("Enemy");
}

void AEnemyFireWorm::BeginPlay()
{
	Super::BeginPlay();

	AController* ControllerBase = GetController();

	AEnemyFireWormAIController* AIController = Cast<AEnemyFireWormAIController>(ControllerBase);

	if(AIController)
	{
		AIController->GetBlackboardComponent()->SetValueAsVector("StartingLocation", GetActorLocation());
		AIController->GetBlackboardComponent()->SetValueAsObject("SelfActor", this);
	}

	if(Idle)
		SetState(Idle);
}

void AEnemyFireWorm::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AEnemyFireWorm::ProccessMovementStateMachine()
{
	if(!IgnoreMovementStateMachine)
	{
		if(GetVelocity() != FVector::ZeroVector)
		{
			MovementDirection = FVector(GetVelocity().X, GetVelocity().Y, GetVelocity().Z);
			
			bool success = MovementDirection.Normalize();

			SetState(Walk);

			if(success)
			{
				if(MovementDirection.Y > 0)
					SetActorRelativeRotation(FQuat(FRotator(0.0, 180.0, 0.0)));
				else if(MovementDirection.Y < 0)
					SetActorRelativeRotation(FQuat(FRotator(0.0, 0.0, 0.0)));
			}
		}
		else
		{
			MovementDirection = FVector::ZeroVector;

			SetState(Idle);
		}
	}
}

float AEnemyFireWorm::ReceiveDamange_Implementation(float DamageAmount, FVector HitDirection)
{
	if(!IsImmune)
	{
		IsImmune = true;
		
		AAIController* AIController = Cast<AAIController>(GetController());

		if(AIController)
		{
			IgnoreMovementStateMachine = true;
		
			AIController->GetBrainComponent()->StopLogic(("HIT"));

			SetState(Hurt);
		}
	
		GetCharacterMovement()->AddImpulse(HitDirection * 1000.0, true);
	}
	
	return 0.0;
}
