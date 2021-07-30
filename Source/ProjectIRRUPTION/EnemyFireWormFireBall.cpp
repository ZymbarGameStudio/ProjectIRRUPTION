// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyFireWormFireBall.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "PaperFlipbookComponent.h"
#include "Components/CapsuleComponent.h"

AEnemyFireWormFireBall::AEnemyFireWormFireBall()
{
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	
	GetSprite()->SetRelativeRotation(FQuat(FRotator(0.0, -90.0, 0.0)));

	ProjectileMovementComponent->ProjectileGravityScale = 0.0;
	ProjectileMovementComponent->InitialSpeed = 100.0;

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AEnemyFireWormFireBall::OnComponentBeginOverlap);
}

void AEnemyFireWormFireBall::BeginPlay()
{
	GetWorld()->GetTimerManager().SetTimer(LifeTimer, this, &AEnemyFireWormFireBall::OnLifeTimeFinished, LifeTime);
	
	if(FireballMovement)
		SetState(FireballMovement);
	
	Super::BeginPlay();
}

void AEnemyFireWormFireBall::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AEnemyFireWormFireBall::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor->ActorHasTag("Player"))
	{
		if(LifeTimer.IsValid())
			GetWorld()->GetTimerManager().ClearTimer(LifeTimer);

		ProjectileMovementComponent->StopMovementImmediately();

		SetState(FireballExplosion);
		
		GEngine->AddOnScreenDebugMessage(rand(), 2, FColor::Cyan, "Explode");
	}
}

UProjectileMovementComponent* AEnemyFireWormFireBall::GetProjectileMovementComponent()
{
	return this->ProjectileMovementComponent;
}

void AEnemyFireWormFireBall::OnLifeTimeFinished()
{
	Destroy();
}