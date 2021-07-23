// Fill out your copyright notice in the Description page of Project Settings.


#include "StateManager.h"

#include "PaperFlipbookComponent.h"

// Sets default values
AStateManager::AStateManager()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AStateManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AStateManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(CurrentState)
		CurrentState->Tick(DeltaTime, this);
}

// Called to bind functionality to input
void AStateManager::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AStateManager::SetState(UState* NewState)
{
	if(CurrentState)
		CurrentState->OnStateExit(this);

	if(NewState->Type == EStateType::MOVIMENTATION)
		CurrentMovimentationState = NewState;

	PreviousState = CurrentState;
	CurrentState = NewState;

	CurrentState->OnStateEnter(this);
}

void AStateManager::SetStateToCurrentMovimentationState()
{
	if(CurrentMovimentationState)
		SetState(CurrentMovimentationState);
}

void AStateManager::SetIgnoreMovementStateMachine(bool Ignore)
{
	IgnoreMovementStateMachine = Ignore;
}

void AStateManager::OnAnimationEnd()
{
	if(OnAnimationEndTimerHandle.IsValid())
		GetWorld()->GetTimerManager().ClearTimer(OnAnimationEndTimerHandle);
	
	CurrentState->OnAnimationEnd_Implementation(this);
}

void AStateManager::SetAnimationEnd()
{
	if(OnAnimationEndTimerHandle.IsValid())
		GetWorld()->GetTimerManager().ClearTimer(OnAnimationEndTimerHandle);
	
	GetWorld()->GetTimerManager().SetTimer(OnAnimationEndTimerHandle, this, &AStateManager::OnAnimationEnd, GetSprite()->GetFlipbookLength());
}
