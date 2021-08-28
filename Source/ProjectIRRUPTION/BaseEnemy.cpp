// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEnemy.h"

#include "Components/ProgressBar.h"
#include "Components/WidgetComponent.h"

ABaseEnemy::ABaseEnemy()
{
	WidgetHealthBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthBarComponent"));

	WidgetHealthBar->SetupAttachment(GetRootComponent());
}

void ABaseEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	CurrentHealth = MaxHealth;
	UpdateHealthBar();
}

void ABaseEnemy::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

float ABaseEnemy::ReceiveDamange_Implementation(float DamageAmount, FVector HitDirection)
{
	CurrentHealth -= DamageAmount;

	UpdateHealthBar();

	return CurrentHealth;
}

void ABaseEnemy::UpdateHealthBar()
{
	UUserWidget* UserWidget = WidgetHealthBar->GetWidget();

	UWidget* ProgressBarWidget = UserWidget->GetWidgetFromName("P_HealthBar");

	if(ProgressBarWidget)
	{
		UProgressBar* ProgressBar = Cast<UProgressBar>(ProgressBarWidget);

		if(ProgressBar)
		{
			ProgressBar->SetPercent(CurrentHealth/MaxHealth);
		}
	}
}
