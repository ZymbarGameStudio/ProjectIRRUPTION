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

	SpringArmComponent->SetRelativeRotation(FQuat(FRotator(0.0f, 90.0f, 0.0f)));
	GetSprite()->SetRelativeRotation(FQuat(FRotator(0.0f, -90.0f, 0.0f)));

	SpringArmComponent->SetupAttachment(GetSprite());
	CameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);

	SpringArmComponent->bUsePawnControlRotation = true;

	this->Tags.Add("Player");

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &APPlayerCharacter::OnCapsuleComponentBeginOverlap);

	GetCharacterMovement()->MaxWalkSpeed = 200;

	CameraComponent->SetProjectionMode(ECameraProjectionMode::Orthographic);

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
	if(Controller != nullptr && AxisValue != 0.0f)
	{
		const FRotator Rotation = GetController()->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		this->MovementDirection = FVector(AxisValue, this->MovementDirection.Y, this->MovementDirection.Z);

		AddMovementInput(Direction, AxisValue);
	}
}

void APPlayerCharacter::MoveSides(float AxisValue)
{
	if(Controller != nullptr && AxisValue != 0.0f)
	{
		const FRotator Rotation = GetController()->GetControlRotation();;
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		
		this->MovementDirection = FVector(this->MovementDirection.X, AxisValue, this->MovementDirection.Z);

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
	if(!IgnoreMovementStateMachine)
	{
		if(MovementDirection != FVector::ZeroVector)
		{
			if(MovementDirection.X > 0)
				SetState(Cast<UState>(IdleUp->GetDefaultObject(true)));
			else if(MovementDirection.X < 0)
				SetState(Cast<UState>(Idle->GetDefaultObject(true)));
			else if(MovementDirection.Y < 0)
				SetState(Cast<UState>(IdleRight->GetDefaultObject(true)));
			else if(MovementDirection.Y > 0)
				SetState(Cast<UState>(IdleLeft->GetDefaultObject(true)));

			MovementDirection = FVector::ZeroVector;
		}
	}
}

void APPlayerCharacter::Attack()
{
	if(CanAttack)
	{
		IgnoreMovementStateMachine = true;
		
		if(CurrentMovimentationState->GetClass() == IdleUp->GetDefaultObject()->GetClass())
			SetState(Cast<UState>(AttackUp->GetDefaultObject(true)));
		else if(CurrentMovimentationState->GetClass() == Idle->GetDefaultObject()->GetClass())
			SetState(Cast<UState>(AttackDown->GetDefaultObject(true)));
		else if(CurrentMovimentationState->GetClass() == IdleRight->GetDefaultObject()->GetClass())
			SetState(Cast<UState>(AttackRight->GetDefaultObject(true)));
		else if(CurrentMovimentationState->GetClass() == IdleLeft->GetDefaultObject()->GetClass())
			SetState(Cast<UState>(AttackLeft->GetDefaultObject(true)));
	}
}

void APPlayerCharacter::CastMeleeAttack(FVector Direction)
{
	FVector Start = GetSprite()->GetComponentLocation() + (Direction * 5);
	FCollisionShape CollisionShape = FCollisionShape::MakeSphere(10.0);
	
	//DrawDebugSphere(GetWorld(), Start, CollisionShape.GetSphereRadius(), 16, FColor::Red, true, 0.1);

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
