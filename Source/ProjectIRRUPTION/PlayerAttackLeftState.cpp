// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAttackLeftState.h"

#include "PaperFlipbookComponent.h"
#include "StateManager.h"

UPlayerAttackLeftState::UPlayerAttackLeftState()
{
	Type = EStateType::COMBAT;
}

void UPlayerAttackLeftState::OnStateEnter_Implementation(AStateManager* StateManager)
{
	StateManager->GetSprite()->SetLooping(false);

	Super::OnStateEnter_Implementation(StateManager);
}
