// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "State.h"
#include "PlayerAttackRightState.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTIRRUPTION_API UPlayerAttackRightState : public UState
{
	GENERATED_BODY()

public:
	UPlayerAttackRightState();

protected:
	virtual void OnStateEnter_Implementation(AStateManager* StateManager) override;
};
