// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "BaseEnemy.h"
#include "StateManager.h"
#include "EnemyFireWorm.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTIRRUPTION_API AEnemyFireWorm : public ABaseEnemy
{
	GENERATED_BODY()

public:
	AEnemyFireWorm();

protected:
	//STATES
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class TSubclassOf<class UState> Idle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class TSubclassOf<class UState> Walk;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class TSubclassOf<class UState> Hurt;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class TSubclassOf<class UState> Attack;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class TSubclassOf<class UState> Die;

public:
	virtual void Tick(float DeltaSeconds) override;
	
	void CastFireBall();

	UArrowComponent* GetSkillPoint();

protected:
	virtual void BeginPlay() override;

	virtual void ProccessMovementStateMachine() override;

	virtual float ReceiveDamange_Implementation(float DamageAmount, FVector HitDirection) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UBoxComponent* BoxComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UArrowComponent* SkillPoint;
};
