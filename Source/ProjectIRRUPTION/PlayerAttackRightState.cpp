// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAttackRightState.h"

#include "PaperFlipbookComponent.h"
#include "StateManager.h"

UPlayerAttackRightState::UPlayerAttackRightState()
{
	Type = EStateType::COMBAT;
}

void UPlayerAttackRightState::OnStateEnter_Implementation(AStateManager* StateManager)
{
	StateManager->GetSprite()->SetLooping(false);

	Super::OnStateEnter_Implementation(StateManager);
}
