// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "State.h"
#include "PlayerAttackUpState.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTIRRUPTION_API UPlayerAttackUpState : public UState
{
	GENERATED_BODY()

public:
	UPlayerAttackUpState();

protected:
	virtual void OnStateEnter_Implementation(AStateManager* StateManager) override;
};
