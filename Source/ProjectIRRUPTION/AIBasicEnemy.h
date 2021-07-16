// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"

#include "AIBasicEnemy.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTIRRUPTION_API AAIBasicEnemy : public AAIController
{
	GENERATED_BODY()

	public:
		AAIBasicEnemy();
		virtual void BeginPlay() override;
		virtual void Tick(float DeltaSeconds) override;

	protected:
		UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = AI)
		UBehaviorTree* BehaviourTree;
};
