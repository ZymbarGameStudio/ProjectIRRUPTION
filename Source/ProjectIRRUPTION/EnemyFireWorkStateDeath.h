// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "State.h"
#include "EnemyFireWorkStateDeath.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTIRRUPTION_API UEnemyFireWorkStateDeath : public UState
{
	GENERATED_BODY()

public:
	UEnemyFireWorkStateDeath();

protected:
	virtual void OnAnimationEnd_Implementation(AStateManager* StateManager) override;
};
