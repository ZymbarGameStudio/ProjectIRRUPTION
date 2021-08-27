// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAttackUpState.h"

#include "PPlayerCharacter.h"
#include "StateManager.h"

UPlayerAttackUpState::UPlayerAttackUpState()
{
	Type = EStateType::COMBAT;
}

void UPlayerAttackUpState::Tick(float DeltaSeconds, AStateManager* StateManager)
{
	APPlayerCharacter* CurrentPlayer = Cast<APPlayerCharacter>(StateManager);

	if(CurrentPlayer)
	{
		CurrentPlayer->CastMeleeAttack(FVector(1.0, 0.0, 0.0));
	}

	Super::Tick(DeltaSeconds, StateManager);
}

void UPlayerAttackUpState::OnAnimationEnd_Implementation(AStateManager* StateManager)
{
	StateManager->SetCanMove(true);
	
	Super::OnAnimationEnd_Implementation(StateManager);
}
