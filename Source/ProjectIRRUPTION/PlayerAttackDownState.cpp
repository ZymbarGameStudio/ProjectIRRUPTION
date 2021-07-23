// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAttackDownState.h"

#include "PaperFlipbookComponent.h"
#include "StateManager.h"

UPlayerAttackDownState::UPlayerAttackDownState()
{
	Type = EStateType::COMBAT;
}

void UPlayerAttackDownState::OnStateEnter_Implementation(AStateManager* StateManager)
{
	StateManager->GetSprite()->SetLooping(false);
	
	Super::OnStateEnter_Implementation(StateManager);
}
