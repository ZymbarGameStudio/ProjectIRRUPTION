// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StateManager.h"
#include "GameFramework/ProjectileMovementComponent.h"

#include "EnemyFireWormFireBall.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTIRRUPTION_API AEnemyFireWormFireBall : public AStateManager
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<class UState> FireballMovement;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<class UState> FireballExplosion;

public:
	AEnemyFireWormFireBall();

	virtual void Tick(float DeltaSeconds) override;

	class UProjectileMovementComponent* GetProjectileMovementComponent();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UProjectileMovementComponent* ProjectileMovementComponent;

	UFUNCTION()
	void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	struct FTimerHandle LifeTimer;
	void OnLifeTimeFinished();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float LifeTime = 5.0;
};
