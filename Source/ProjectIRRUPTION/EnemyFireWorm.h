// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StateManager.h"
#include "EnemyFireWorm.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTIRRUPTION_API AEnemyFireWorm : public AStateManager
{
	GENERATED_BODY()

public:
	AEnemyFireWorm();

protected:
	//STATES
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class TSubclassOf<UState> Idle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class TSubclassOf<UState> Walk;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class TSubclassOf<UState> Hurt;

public:
	virtual void Tick(float DeltaSeconds) override;

protected:
	virtual void BeginPlay() override;

	virtual void ProccessMovementStateMachine() override;

	virtual float ReceiveDamange_Implementation(float DamageAmount, FVector HitDirection) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UBoxComponent* BoxComponent;

};
