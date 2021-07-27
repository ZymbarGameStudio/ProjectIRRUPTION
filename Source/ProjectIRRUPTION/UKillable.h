// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UKillable.generated.h"

UINTERFACE()
class UKillable : public UInterface
{
	GENERATED_BODY()

};

class IKillable
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	float ReceiveDamange(float DamageAmount, FVector HitDirection = FVector(0.0, 0.0, 0.0));
};