// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAttackLeftState.h"

#include "DrawDebugHelpers.h"
#include "PaperFlipbookComponent.h"
#include "StateManager.h"

UPlayerAttackLeftState::UPlayerAttackLeftState()
{
	Type = EStateType::COMBAT;
}

void UPlayerAttackLeftState::Tick(float DeltaSeconds, AStateManager* StateManager)
{
	FVector MovementDirection = FVector(0.0, 1.0, 0.0);
	FVector Start = StateManager->GetSprite()->GetComponentLocation() + (MovementDirection * 5.0);
	FCollisionShape CollisionShape = FCollisionShape::MakeSphere(10.0);
	
	DrawDebugSphere(StateManager->GetWorld(), Start, CollisionShape.GetSphereRadius(), 16, FColor::Red, true, 2);

	TArray<FHitResult> OutHits;
	
	bool Success = StateManager->GetWorld()->SweepMultiByChannel(OutHits, Start, Start, FQuat::Identity, ECollisionChannel::ECC_Pawn, CollisionShape);

	if(Success)
	{
		for(FHitResult& Hit: OutHits)
		{
			AActor* Target = Hit.GetActor();

			if(Target->ActorHasTag("Enemy"))
			{
				GEngine->AddOnScreenDebugMessage(rand(), 2, FColor::Cyan, "ENEMY");
			}
		}
	}
}
