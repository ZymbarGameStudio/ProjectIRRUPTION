// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "PaperCharacter.h"
#include "State.h"
#include "GameFramework/Character.h"
#include "StateManager.generated.h"

UCLASS()
class PROJECTIRRUPTION_API AStateManager : public APaperCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AStateManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	class UState* CurrentState;
	class UState* PreviousState;
	class UState* CurrentMovimentationState;

	struct FVector MovementDirection = FVector::ZeroVector;

	bool IgnoreMovementStateMachine = false;
	
	bool CanAttack = true;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void SetState(UState* NewState);

	virtual void SetStateToCurrentMovimentationState();

	UFUNCTION()
	void OnStateAnimationEnd();

	void SetIgnoreMovementStateMachine(bool Ignore);
};
