// Fill out your copyright notice in the Description page of Project Settings.


#include "PPlayerCharacter.h"

#include "DrawDebugHelpers.h"
#include "IdleState.h"
#include "IInteractable.h"
#include "PaperFlipbookComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Perception/AIPerceptionComponent.h"

APPlayerCharacter::APPlayerCharacter()
{
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));

	SpringArmComponent->SetupAttachment(GetRootComponent());
	CameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);

	SpringArmComponent->bUsePawnControlRotation = true;

	this->Tags.Add("Player");

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &APPlayerCharacter::OnCapsuleComponentBeginOverlap);

	GetCharacterMovement()->MaxWalkSpeed = 200;

	CameraComponent->SetProjectionMode(ECameraProjectionMode::Perspective);

	GetCapsuleComponent()->SetCapsuleHalfHeight(16.0f);
	GetCapsuleComponent()->SetCapsuleRadius(4.0f);
	GetCapsuleComponent()->ComponentTags.Add("PlayerCollider");
}

void APPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	if(Idle)
		SetState(Cast<UState>(Idle->GetDefaultObject(true)));
}

void APPlayerCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}


void APPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &APPlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveSides", this, &APPlayerCharacter::MoveSides);

	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &APPlayerCharacter::Interact);
	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &APPlayerCharacter::Attack);
}


void APPlayerCharacter::MoveForward(float AxisValue)
{
	if(Controller != nullptr && AxisValue != 0.0f && CanMove)
	{
		const FRotator Rotation = GetController()->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		MovementDirection = FVector(MovementDirection.X, AxisValue, MovementDirection.Z);
		
		AddMovementInput(Direction, AxisValue);
	}
}

void APPlayerCharacter::MoveSides(float AxisValue)
{
	if(Controller != nullptr && AxisValue != 0.0f && CanMove)
	{
		const FRotator Rotation = GetController()->GetControlRotation();;
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		
		MovementDirection = FVector(AxisValue, MovementDirection.Y, MovementDirection.Z);
		
		AddMovementInput(Direction, AxisValue);
	}
}

void APPlayerCharacter::OnCapsuleComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(rand(), 2, FColor::Cyan, FString::Printf(TEXT("Colidiu")));
}

void APPlayerCharacter::SetInteractable(TScriptInterface<IInteractable> NewInteractable)
{
	this->Interactable = NewInteractable;
}

void APPlayerCharacter::Interact()
{
	if(Interactable)
		Interactable->Interact();
}

void APPlayerCharacter::ProccessMovementStateMachine()
{
	Super::ProccessMovementStateMachine();
	
	if(!IgnoreMovementStateMachine)
	{
		if(GetVelocity() != FVector::ZeroVector)
		{
			if(MovementDirection.Y > 0)
				SetState(WalkDown);
			else if(MovementDirection.Y < 0)
				SetState(WalkUp);
			else if(MovementDirection.X != 0)
				SetState(WalkSides);
		}
		else
		{
			if(CurrentMovimentationState->GetClass() == WalkDown->GetDefaultObject()->GetClass())
				SetState(Idle);
			else if (CurrentMovimentationState->GetClass() == WalkUp->GetDefaultObject()->GetClass())
				SetState(IdleUp);
			else if (CurrentMovimentationState->GetClass() == WalkSides->GetDefaultObject()->GetClass())
				SetState(IdleRight);
		}

		MovementDirection = FVector::ZeroVector;
	}
}

void APPlayerCharacter::Attack()
{
	if(CanAttack)
	{
		IgnoreMovementStateMachine = true;
		
		if(CurrentMovimentationState->GetClass() == IdleUp->GetDefaultObject()->GetClass() || CurrentMovimentationState->GetClass() == WalkUp->GetDefaultObject()->GetClass())
			SetState(AttackUp);
		else if(CurrentMovimentationState->GetClass() == Idle->GetDefaultObject()->GetClass() || CurrentMovimentationState->GetClass() == WalkDown->GetDefaultObject()->GetClass())
			SetState(AttackDown);
		else if(CurrentMovimentationState->GetClass() == IdleRight->GetDefaultObject()->GetClass() || CurrentMovimentationState->GetClass() == WalkSides->GetDefaultObject()->GetClass())
			SetState(AttackRight);
	}
}

void APPlayerCharacter::CastMeleeAttack(FVector Direction)
{
	CanMove = false;
	
	FVector Start = GetSprite()->GetComponentLocation() + (Direction * 10);
	FCollisionShape CollisionShape = FCollisionShape::MakeSphere(15.0);
	
	// DrawDebugSphere(GetWorld(), Start, CollisionShape.GetSphereRadius(), 16, FColor::Red, true, 0.1);

	TArray<FHitResult> OutHits;

	bool Success = GetWorld()->SweepMultiByChannel(OutHits, Start, Start, FQuat::Identity, ECollisionChannel::ECC_Pawn, CollisionShape);

	if(Success)
	{
		for (FHitResult& Hit: OutHits)
		{
			AActor* Target = Hit.GetActor();

			if(Target->ActorHasTag("Enemy"))
			{
				IKillable* Enemy = Cast<IKillable>(Target);

				if(Enemy)
				{
					Enemy->Execute_ReceiveDamange(Target, 1, Direction);
				}
			}
		}
	}
}
