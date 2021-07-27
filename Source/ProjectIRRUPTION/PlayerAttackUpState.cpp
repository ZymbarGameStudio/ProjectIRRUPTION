// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAttackUpState.h"

#include "DrawDebugHelpers.h"
#include "PaperFlipbookComponent.h"
#include "StateManager.h"
#include "GameFramework/CharacterMovementComponent.h"

UPlayerAttackUpState::UPlayerAttackUpState()
{
	Type = EStateType::COMBAT;
}

void UPlayerAttackUpState::Tick(float DeltaSeconds, AStateManager* StateManager)
{
	FVector MovementDirection = FVector(1.0, 0.0, 0.0);
	FVector Start = StateManager->GetSprite()->GetComponentLocation() + (MovementDirection * 5);
	FCollisionShape CollisionShape = FCollisionShape::MakeSphere(10.0);
	
	DrawDebugSphere(StateManager->GetWorld(), Start, CollisionShape.GetSphereRadius(), 16, FColor::Red, true, 0.1);

	TArray<FHitResult> OutHits;

	bool Success = StateManager->GetWorld()->SweepMultiByChannel(OutHits, Start, Start, FQuat::Identity, ECollisionChannel::ECC_Pawn, CollisionShape);

	if(Success)
	{
		for (FHitResult& Hit: OutHits)
		{
			AActor* Target = Hit.GetActor();

			if(Target->ActorHasTag("Enemy"))
			{
				IKillable* Enemy = Cast<IKillable>(Target);

				if(Enemy)
				{
					GEngine->AddOnScreenDebugMessage(rand(), 2, FColor::Cyan, "ENEMY");
					Enemy->Execute_ReceiveDamange(Target, 1, MovementDirection);
				}
			}
		}
	}
}
