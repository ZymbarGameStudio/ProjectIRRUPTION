// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "MyBTTaskNode.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTIRRUPTION_API UMyBTTaskNode : public UBTTaskNode
{
	GENERATED_BODY()

	protected:
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FBlackboardKeySelector Key;
};
