// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StateManager.h"
#include "BaseEnemy.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTIRRUPTION_API ABaseEnemy : public AStateManager, public IKillable
{
	GENERATED_BODY()

public:
	ABaseEnemy();
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxHealth;

	UPROPERTY(BlueprintReadWrite)
	float CurrentHealth;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class UWidgetComponent* WidgetHealthBar;

public:
	virtual void Tick(float DeltaSeconds) override;

protected:
	
	virtual void BeginPlay() override;

	virtual float ReceiveDamange_Implementation(float DamageAmount, FVector HitDirection) override;

	void UpdateHealthBar();
};
