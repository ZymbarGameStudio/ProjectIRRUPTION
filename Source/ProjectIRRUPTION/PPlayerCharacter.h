// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "PaperFlipbook.h"
#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "StateManager.h"
#include "Perception/AIPerceptionTypes.h"

#include "PPlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTIRRUPTION_API APPlayerCharacter : public AStateManager
{
	GENERATED_BODY()

protected:
	// MOVEMENT STATES
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Animations)
	TSubclassOf<class UState> Idle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Animations)
	TSubclassOf<class UState> IdleLeft;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Animations)
	TSubclassOf<class UState> IdleRight;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Animations)
	TSubclassOf<class UState> IdleUp;

	// ATTACK STATES
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Animations)
	TSubclassOf<class UState> AttackDown;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Animations)
	TSubclassOf<class UState> AttackLeft;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Animations)
	TSubclassOf<class UState> AttackRight;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Animations)
	TSubclassOf<class UState> AttackUp;

public:
	APPlayerCharacter();
	
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	
	UFUNCTION()
	void OnCapsuleComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
	void SetInteractable(TScriptInterface<class IInteractable> NewInteractable);

protected:
	// INPUT/ACTIONS
	
	void MoveForward(float AxisValue);
	
	void MoveSides(float AxisValue);
	
	void Interact();

	void Attack();

	// ENGINE
	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaSeconds) override;
	
	// STATE MACHINE
	virtual void ProcessMovementStateMachine() override;
	
	//CAMERA
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class USpringArmComponent* SpringArmComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UCameraComponent* CameraComponent;

	//INTERACTABLE
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TScriptInterface<class IInteractable> Interactable;
};
