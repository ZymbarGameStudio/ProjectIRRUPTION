// Fill out your copyright notice in the Description page of Project Settings.


#include "State.h"

#include "PaperFlipbookComponent.h"
#include "StateManager.h"

UState::UState()
{
	
}

void UState::OnStateEnter_Implementation(class AStateManager* StateManager)
{
	StateManager->GetSprite()->SetFlipbook(this->Animation);
	StateManager->GetSprite()->OnFinishedPlaying.AddDynamic(this, &UState::OnAnimationEnd_Implementation);
}

void UState::OnStateExit_Implementation(class AStateManager* StateManager)
{
	
}

void UState::Tick_Implementation(float DeltaSeconds, class AStateManager* StateManager)
{
	
}

void UState::OnAnimationEnd_Implementation()
{
	GEngine->AddOnScreenDebugMessage(rand(), 2, FColor::Blue,  "Finished Animation");
}