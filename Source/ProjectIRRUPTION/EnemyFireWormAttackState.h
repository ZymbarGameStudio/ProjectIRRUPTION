// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "State.h"
#include "EnemyFireWormAttackState.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTIRRUPTION_API UEnemyFireWormAttackState : public UState
{
	GENERATED_BODY()

public:
	UEnemyFireWormAttackState();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class AStateManager> Skill;

protected:
	virtual void OnStateEnter_Implementation(AStateManager* StateManager) override;

	struct FTimerHandle AttackTimer;
	void OnAttack();

	class AStateManager* CurrentStateManager;
};
