// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyFireBallExplosionState.h"

#include "StateManager.h"

UEnemyFireBallExplosionState::UEnemyFireBallExplosionState()
{
	Type = EStateType::COMBAT;
}

void UEnemyFireBallExplosionState::OnAnimationEnd_Implementation(AStateManager* StateManager)
{
	StateManager->Destroy();
	
	Super::OnAnimationEnd_Implementation(StateManager);
}