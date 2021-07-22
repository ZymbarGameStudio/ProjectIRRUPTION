// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "Components/TextBlock.h"
#include "GameFramework/GameModeBase.h"
#include "ProjectIRRUPTIONGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTIRRUPTION_API AProjectIRRUPTIONGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	public:
		AProjectIRRUPTIONGameModeBase();

		UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		bool HasKey = false;
	
		UFUNCTION(BlueprintCallable)
		void UseKey();
		UFUNCTION(BlueprintCallable)
		void CollectKey();
		UFUNCTION(BlueprintCallable)
		void SetHintText(FString Text);
		UFUNCTION()
		void RemoveWidget();

	protected:
		virtual void BeginPlay() override;
	
		void InitializeHUD();

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Widget)
		TSubclassOf<UUserWidget> WidgetReference;
	
		UPROPERTY()
		UUserWidget* MainWidget;
	
		UPROPERTY()
		UTextBlock* HintText;
};
