// Copyright Epic Games, Inc. All Rights Reserved.


#include "ProjectIRRUPTIONGameModeBase.h"

#include "Blueprint/UserWidget.h"
#include "Components/EditableText.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

AProjectIRRUPTIONGameModeBase::AProjectIRRUPTIONGameModeBase()
{
	
}

void AProjectIRRUPTIONGameModeBase::BeginPlay()
{
	this->InitializeHUD();
}


void AProjectIRRUPTIONGameModeBase::UseKey()
{
	if(HasKey)
	{
		HasKey = false;
	}
}

void AProjectIRRUPTIONGameModeBase::CollectKey()
{
	HasKey = true;
}

void AProjectIRRUPTIONGameModeBase::InitializeHUD()
{
	MainWidget = CreateWidget<UUserWidget>(GetWorld(), WidgetReference);

	if(MainWidget)
	{
		UWidget* Hint = MainWidget->GetWidgetFromName(TEXT("T_Hint"));

		if(Hint)
			HintText = Cast<UTextBlock>(Hint);
	}
}

void AProjectIRRUPTIONGameModeBase::SetHintText(FString Text)
{
	if(MainWidget)
	{
		if(!MainWidget->IsInViewport())
			MainWidget->AddToViewport();
		
		HintText->SetText(FText::FromString(Text));
	}
}

void AProjectIRRUPTIONGameModeBase::RemoveWidget()
{
	if(MainWidget)
	{
		if(MainWidget->IsInViewport())
			MainWidget->RemoveFromViewport();
	}
}
