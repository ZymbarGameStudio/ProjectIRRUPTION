// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "State.h"
#include "PlayerAttackDownState.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTIRRUPTION_API UPlayerAttackDownState : public UState
{
	GENERATED_BODY()

public:
	UPlayerAttackDownState();

protected:
	virtual void Tick(float DeltaSeconds, AStateManager* StateManager) override;	
};
