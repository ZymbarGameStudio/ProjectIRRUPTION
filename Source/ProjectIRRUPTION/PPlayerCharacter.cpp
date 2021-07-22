// Fill out your copyright notice in the Description page of Project Settings.


#include "PPlayerCharacter.h"

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
}

void APPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	if(Idle)
		SetState(Cast<UState>(Idle->GetDefaultObject(true)));
}

void APPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &APPlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveSides", this, &APPlayerCharacter::MoveSides);
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &APPlayerCharacter::Interact);
}


void APPlayerCharacter::MoveForward(float AxisValue)
{
	if(Controller != nullptr && AxisValue != 0.0f)
	{
		const FRotator Rotation = GetController()->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

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
