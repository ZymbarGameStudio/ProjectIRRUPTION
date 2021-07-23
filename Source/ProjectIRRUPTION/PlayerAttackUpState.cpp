// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAttackUpState.h"

#include "PaperFlipbookComponent.h"
#include "StateManager.h"

UPlayerAttackUpState::UPlayerAttackUpState()
{
	Type = EStateType::COMBAT;
}

void UPlayerAttackUpState::OnStateEnter_Implementation(AStateManager* StateManager)
{
	StateManager->GetSprite()->SetLooping(false);

	Super::OnStateEnter_Implementation(StateManager);
}
