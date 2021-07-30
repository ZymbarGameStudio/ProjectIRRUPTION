// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "State.h"
#include "EnemyFireWormHurtState.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTIRRUPTION_API UEnemyFireWormHurtState : public UState
{
	GENERATED_BODY()

public:
	UEnemyFireWormHurtState();

protected:
	virtual void OnAnimationEnd_Implementation(AStateManager* StateManager) override;

	virtual void Tick(float DeltaSeconds, AStateManager* StateManager) override;

	int ColorCounter = 0;
};
