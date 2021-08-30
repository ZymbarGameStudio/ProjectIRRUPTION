// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyFireWorm.h"

#include "BrainComponent.h"
#include "EnemyFireWormAIController.h"
#include "PaperFlipbookComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

AEnemyFireWorm::AEnemyFireWorm()
{
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	SkillPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowComponent"));
	
	BoxComponent->SetupAttachment(GetRootComponent());
	SkillPoint->SetupAttachment(GetSprite());
	
	GetSprite()->SetRelativeLocationAndRotation(FVector(0.0, 0.0, 10.0), FQuat(FRotator(0.0, 0.0, 0.0)));
	BoxComponent->SetRelativeLocationAndRotation(FVector(0.0, 0.0, 10.0), FQuat(FRotator(0.0, 0.0, 0.0)));
	
	GetCapsuleComponent()->SetCapsuleHalfHeight(10.0);
	GetCapsuleComponent()->SetCapsuleRadius(10.0);
	BoxComponent->SetBoxExtent(FVector(21.0, 3.0, 13.0));

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
	Super::ProccessMovementStateMachine();
	
	if(!IgnoreMovementStateMachine)
	{
		if(GetVelocity() == FVector::ZeroVector)
		{
			SetState(Idle);
		}
	}
}

float AEnemyFireWorm::ReceiveDamange_Implementation(float DamageAmount, FVector HitDirection)
{
	if(!IsImmune)
	{
		Super::ReceiveDamange_Implementation(DamageAmount, HitDirection);
		
		IsImmune = true;
		IgnoreMovementStateMachine = true;
		
		AAIController* AIController = Cast<AAIController>(GetController());
		
		if(AIController)
			AIController->GetBrainComponent()->StopLogic(("HIT"));
		
		if(CurrentHealth <= 0)
			SetState(Die);
		else
			SetState(Hurt);
		
		GetCharacterMovement()->AddImpulse(HitDirection * 1000.0, true);
	}
	
	return CurrentHealth;
}

void AEnemyFireWorm::CastFireBall()
{
	if (CanAttack)
	{
		IgnoreMovementStateMachine = true;

		SetState(Attack);
	}
}

UArrowComponent* AEnemyFireWorm::GetSkillPoint()
{
	return this->SkillPoint;
}
