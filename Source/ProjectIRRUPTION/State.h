// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Paper2D/Classes/PaperFlipbook.h"

#include "CoreMinimal.h"
#include "State.generated.h"

UCLASS(Blueprintable)
class UState: public UObject
{
	GENERATED_BODY()

public:
	UState();

	TEnumAsByte<enum EStateType> Type;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class UPaperFlipbook* Animation;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnStateEnter(class AStateManager* StateManager);

	virtual void Tick(float DeltaSeconds, class AStateManager* StateManager);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnStateExit(class AStateManager* StateManager);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnAnimationEnd(class AStateManager* StateManager);
};

UENUM()
enum EStateType
{
	MOVIMENTATION,
	COMBAT
};
