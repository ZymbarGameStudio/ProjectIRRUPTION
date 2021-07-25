// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAttackDownState.h"

#include "DrawDebugHelpers.h"
#include "PaperFlipbookComponent.h"
#include "StateManager.h"

UPlayerAttackDownState::UPlayerAttackDownState()
{
	Type = EStateType::COMBAT;
}

void UPlayerAttackDownState::Tick(float DeltaSeconds, AStateManager* StateManager)
{
	TArray<FHitResult> OutHits;
	
	float HitLength = 10.0;
	FVector Start = StateManager->GetSprite()->GetComponentLocation() + (FVector(-1.0, 0.0, 0.0) * 5);
	FVector End = Start + (FVector(-1.0, 0.0, 0.0) * HitLength);
	FCollisionShape CollisionShape = FCollisionShape::MakeSphere(10.0f);

	//DrawDebugSphere(StateManager->GetWorld(), End, CollisionShape.GetSphereRadius(), 16, FColor::Red, true);
	bool success = StateManager->GetWorld()->SweepMultiByChannel(OutHits, End, End, FQuat::Identity, ECollisionChannel::ECC_Pawn, CollisionShape);

	if(success)
	{
		for (FHitResult& Hit: OutHits)
		{
			AActor* Target = Hit.GetActor();
		
			if(Target)
			{
				if(Target->ActorHasTag("Enemy"))
				{
					GEngine->AddOnScreenDebugMessage(rand(), 2, FColor::Cyan, "ENEMY");
				}
			}
		}
	}
}
