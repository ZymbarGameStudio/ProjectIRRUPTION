// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IInteractable.generated.h"

UINTERFACE(MinimalAPI, Blueprintable)
class UInteractable: public UInterface
{
	GENERATED_BODY()
};

class IInteractable
{
	GENERATED_BODY()

	public:
		virtual void Interact();
};