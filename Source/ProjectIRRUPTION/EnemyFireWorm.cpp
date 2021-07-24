// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyFireWorm.h"

#include "PaperFlipbookComponent.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"

AEnemyFireWorm::AEnemyFireWorm()
{
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));

	BoxComponent->SetupAttachment(GetRootComponent());
	
	GetSprite()->SetRelativeLocationAndRotation(FVector(0.0, 0.0, 10.0), FQuat(FRotator(0.0, -90.0, 0.0)));
	BoxComponent->SetRelativeLocation(FVector(0.0, 0.0, 10.0));
	
	GetCapsuleComponent()->SetCapsuleHalfHeight(10.0);
	GetCapsuleComponent()->SetCapsuleRadius(10.0);
	BoxComponent->SetBoxExtent(FVector(3.0, 21.0, 13.0));

	BoxComponent->SetCollisionResponseToChannels(ECollisionResponse::ECR_Overlap);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
}

void AEnemyFireWorm::BeginPlay()
{
	Super::BeginPlay();

	if(Idle)
		SetState(Idle);
}

void AEnemyFireWorm::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

