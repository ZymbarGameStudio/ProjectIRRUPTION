// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "State.h"
#include "EnemyFireBallExplosionState.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTIRRUPTION_API UEnemyFireBallExplosionState : public UState
{
	GENERATED_BODY()

public:
	UEnemyFireBallExplosionState();

protected:
	virtual void OnAnimationEnd_Implementation(AStateManager* StateManager) override;
};
