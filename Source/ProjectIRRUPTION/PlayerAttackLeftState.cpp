// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAttackLeftState.h"

#include "DrawDebugHelpers.h"
#include "PaperFlipbookComponent.h"
#include "PPlayerCharacter.h"
#include "StateManager.h"

UPlayerAttackLeftState::UPlayerAttackLeftState()
{
	Type = EStateType::COMBAT;
}

void UPlayerAttackLeftState::Tick(float DeltaSeconds, AStateManager* StateManager)
{
	APPlayerCharacter* CurrentPlayer = Cast<APPlayerCharacter>(StateManager);

	if(CurrentPlayer)
	{
		CurrentPlayer->CastMeleeAttack(FVector(0.0, 1.0, 0.0));
	}

	Super::Tick(DeltaSeconds, StateManager);
}
