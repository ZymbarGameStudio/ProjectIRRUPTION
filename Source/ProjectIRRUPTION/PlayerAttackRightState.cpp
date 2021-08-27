// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAttackRightState.h"

#include "PPlayerCharacter.h"
#include "StateManager.h"

UPlayerAttackRightState::UPlayerAttackRightState()
{
	Type = EStateType::COMBAT;
}

void UPlayerAttackRightState::Tick(float DeltaSeconds, AStateManager* StateManager)
{
	APPlayerCharacter* CurrentPlayer = Cast<APPlayerCharacter>(StateManager);

	if(CurrentPlayer)
	{
		CurrentPlayer->CastMeleeAttack(FVector(0.0, -1.0, 0.0));
	}

	Super::Tick(DeltaSeconds, StateManager);
}

void UPlayerAttackRightState::OnAnimationEnd_Implementation(AStateManager* StateManager)
{
	StateManager->SetCanMove(true);
	
	Super::OnAnimationEnd_Implementation(StateManager);
}
