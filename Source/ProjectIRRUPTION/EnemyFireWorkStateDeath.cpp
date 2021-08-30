// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyFireWorkStateDeath.h"

#include "StateManager.h"

UEnemyFireWorkStateDeath::UEnemyFireWorkStateDeath()
{
	Type = EStateType::COMBAT;
}

void UEnemyFireWorkStateDeath::OnAnimationEnd_Implementation(AStateManager* StateManager)
{
	StateManager->Destroy();
}
