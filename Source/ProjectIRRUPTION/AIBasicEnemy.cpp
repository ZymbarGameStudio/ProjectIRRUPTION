// Fill out your copyright notice in the Description page of Project Settings.


#include "AIBasicEnemy.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"

AAIBasicEnemy::AAIBasicEnemy()
{
	
}

void AAIBasicEnemy::BeginPlay()
{
	Super::BeginPlay();

	bool running =this->RunBehaviorTree(BehaviourTree);

	if(running)
	{
		GetBlackboardComponent()->SetValueAsVector(TEXT("StartingLocation"), GetCharacter()->GetActorLocation());
	}
}

void AAIBasicEnemy::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}
