// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "PaperFlipbook.h"
#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "Perception/AIPerceptionTypes.h"

#include "PPlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTIRRUPTION_API APPlayerCharacter : public APaperCharacter
{
	GENERATED_BODY()

	public:
		APPlayerCharacter();
		virtual void Tick(float Deltatime) override;
		virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
		UFUNCTION()
		void OnCapsuleComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	
	protected:
		virtual void BeginPlay() override;

		UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Flipbook)
		class UPaperFlipbook* IdleFlipBook;

		UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class USpringArmComponent* SpringArmComponent;
		
		UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UCameraComponent* CameraComponent;

		void MoveForward(float AxisValue);
		void MoveSides(float AxisValue);

	
};
