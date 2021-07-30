// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyFireWormHurtState.h"

#include "AIController.h"
#include "BrainComponent.h"
#include "PaperFlipbookComponent.h"
#include "StateManager.h"

UEnemyFireWormHurtState::UEnemyFireWormHurtState()
{
	Type = EStateType::COMBAT;
}

void UEnemyFireWormHurtState::Tick(float DeltaSeconds, AStateManager* StateManager)
{
	ColorCounter++;

	if(ColorCounter % 2 == 0)
		StateManager->GetSprite()->SetSpriteColor(FLinearColor(FColor::Red));
	else
		StateManager->GetSprite()->SetSpriteColor(FLinearColor(FColor::White));
	
	Super::Tick(DeltaSeconds, StateManager);
}


void UEnemyFireWormHurtState::OnAnimationEnd_Implementation(AStateManager* StateManager)
{
	AAIController* AIController = Cast<AAIController>(StateManager->GetController());

	if(AIController)
	{
		StateManager->SetIsImmune(false);
		
		StateManager->GetSprite()->SetSpriteColor(FLinearColor(FColor::White));
		
		StateManager->SetIgnoreMovementStateMachine(false);

		AIController->GetBrainComponent()->RestartLogic();
	}
	
	Super::OnAnimationEnd_Implementation(StateManager);
}
