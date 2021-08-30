// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAttackDownState.h"

#include "PPlayerCharacter.h"
#include "StateManager.h"

UPlayerAttackDownState::UPlayerAttackDownState()
{
	Type = EStateType::COMBAT;
}

void UPlayerAttackDownState::Tick(float DeltaSeconds, AStateManager* StateManager)
{
	APPlayerCharacter* CurrentPlayer = Cast<APPlayerCharacter>(StateManager);

	if(CurrentPlayer)
	{
		CurrentPlayer->CastMeleeAttack(FVector(0.0, 1.0, 0.0));
	}

	Super::Tick(DeltaSeconds, StateManager);
}

void UPlayerAttackDownState::OnAnimationEnd_Implementation(AStateManager* StateManager)
{
	StateManager->SetCanMove(true);
	
	Super::OnAnimationEnd_Implementation(StateManager);
}
