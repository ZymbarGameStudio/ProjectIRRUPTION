// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyFireWormAIController.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"

AEnemyFireWormAIController::AEnemyFireWormAIController()
{
	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComponent"));

	AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AEnemyFireWormAIController::OnTargetPerceptionUpdated);
}

void AEnemyFireWormAIController::BeginPlay()
{
	Super::BeginPlay();

	if(BehaviorTree)
	{
		bool success = RunBehaviorTree(BehaviorTree);
	}
}


void AEnemyFireWormAIController::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	if(Actor->ActorHasTag("Player"))
	{
		GetBlackboardComponent()->SetValueAsObject("Target", Actor);
	}
}
