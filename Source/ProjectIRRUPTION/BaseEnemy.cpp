// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEnemy.h"

#include "Components/WidgetComponent.h"

ABaseEnemy::ABaseEnemy()
{
	WidgetHealthBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthBarComponent"));
}

void ABaseEnemy::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;
}

void ABaseEnemy::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

