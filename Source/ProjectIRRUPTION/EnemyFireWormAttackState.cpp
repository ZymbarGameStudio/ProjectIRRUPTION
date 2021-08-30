// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyFireWormAttackState.h"

#include "AIController.h"
#include "EnemyFireWorm.h"
#include "EnemyFireWormFireBall.h"
#include "PaperFlipbookComponent.h"
#include "StateManager.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/ArrowComponent.h"

UEnemyFireWormAttackState::UEnemyFireWormAttackState()
{
	Type = EStateType::COMBAT;
}

void UEnemyFireWormAttackState::OnStateEnter_Implementation(AStateManager* StateManager)
{
	CurrentStateManager = StateManager;
	
	if(AttackTimer.IsValid())
		StateManager->GetWorld()->GetTimerManager().ClearTimer(AttackTimer);
	
	Super::OnStateEnter_Implementation(StateManager);

	StateManager->GetWorld()->GetTimerManager().SetTimer(AttackTimer, this, &UEnemyFireWormAttackState::OnAttack, StateManager->GetSprite()->GetFlipbookLength() * 0.733);
}

void UEnemyFireWormAttackState::OnAttack()
{
	AAIController* AIController = Cast<AAIController>(CurrentStateManager->GetController());

	UObject* TargetObject = AIController->GetBlackboardComponent()->GetValueAsObject("Target");

	if(TargetObject)
	{
		AActor* Target = Cast<AActor>(TargetObject);

		if(Target)
		{
			AEnemyFireWorm* FireWorm = Cast<AEnemyFireWorm>(CurrentStateManager);
			
			if(FireWorm)
			{
				FVector Direction = Target->GetActorLocation() - FireWorm->GetSprite()->GetComponentLocation();
				FRotator Rotation;
				
				if(Direction.X > 0)
					Rotation = FRotator(0.0, 0.0, 0.0);
				else if(Direction.X < 0)
					Rotation = FRotator(0.0, 180.0, 0.0);

				FireWorm->GetSprite()->SetRelativeRotation(FQuat(Rotation));
			
				FActorSpawnParameters SpawnParameters;
				AEnemyFireWormFireBall* FireBall = FireWorm->GetWorld()->SpawnActor<AEnemyFireWormFireBall>(Skill, FireWorm->GetSkillPoint()->GetComponentLocation(), Rotation, SpawnParameters);

				if(FireBall)
				{
					FireBall->GetProjectileMovementComponent()->Velocity = Direction;
					
					GEngine->AddOnScreenDebugMessage(rand(), 2, FColor::Cyan, "Fireball");
				}
			}
		}
	}
}

void UEnemyFireWormAttackState::OnAnimationEnd_Implementation(AStateManager* StateManager)
{
	if(AttackTimer.IsValid())
		StateManager->GetWorld()->GetTimerManager().ClearTimer(AttackTimer);

	Super::OnAnimationEnd_Implementation(StateManager);
}

void UEnemyFireWormAttackState::OnStateExit_Implementation(AStateManager* StateManager)
{
	if(AttackTimer.IsValid())
		StateManager->GetWorld()->GetTimerManager().ClearTimer(AttackTimer);

	Super::OnStateExit_Implementation(StateManager);
}
