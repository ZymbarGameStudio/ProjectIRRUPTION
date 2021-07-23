// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "State.h"
#include "PlayerAttackLeftState.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTIRRUPTION_API UPlayerAttackLeftState : public UState
{
	GENERATED_BODY()

public:
	UPlayerAttackLeftState();

protected:
	virtual void OnStateEnter_Implementation(AStateManager* StateManager) override;
};
