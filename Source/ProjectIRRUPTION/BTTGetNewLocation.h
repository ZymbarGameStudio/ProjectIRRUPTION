// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTGetNewLocation.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTIRRUPTION_API UBTTGetNewLocation : public UBTTaskNode
{
	GENERATED_BODY()

	public:
		UBTTGetNewLocation();
	
		virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
