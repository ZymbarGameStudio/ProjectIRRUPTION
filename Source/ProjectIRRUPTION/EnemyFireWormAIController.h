// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"

#include "EnemyFireWormAIController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTIRRUPTION_API AEnemyFireWormAIController : public AAIController
{
	GENERATED_BODY()

public:
	AEnemyFireWormAIController();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class UBehaviorTree* BehaviorTree;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UAIPerceptionComponent* AIPerceptionComponent;

	UFUNCTION()
	void OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);
};
