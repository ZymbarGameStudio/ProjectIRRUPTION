// Fill out your copyright notice in the Description page of Project Settings.


#include "State.h"

#include "PaperFlipbookComponent.h"
#include "StateManager.h"

UState::UState()
{
}

void UState::OnStateEnter_Implementation(class AStateManager* StateManager)
{
	StateManager->GetSprite()->SetFlipbook(this->Animation);
	
	if(Type == EStateType::COMBAT)
		StateManager->SetAnimationEnd();
}

void UState::OnStateExit_Implementation(class AStateManager* StateManager)
{
	
}

void UState::Tick_Implementation(float DeltaSeconds, class AStateManager* StateManager)
{
	
}

void UState::OnAnimationEnd_Implementation(class AStateManager* StateManager)
{
	if(Type == EStateType::COMBAT)
	{
		StateManager->SetIgnoreMovementStateMachine(false);

		StateManager->SetStateToCurrentMovimentationState();
	}
}
