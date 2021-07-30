// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTEnemyFireWormFireBallAttack.h"

#include "AIController.h"
#include "EnemyFireWorm.h"

EBTNodeResult::Type UBTTEnemyFireWormFireBallAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	APawn* ControlledPawn = OwnerComp.GetAIOwner()->GetPawn();

	AEnemyFireWorm* FireWorm = Cast<AEnemyFireWorm>(ControlledPawn);

	if(FireWorm)
	{
		FireWorm->CastFireBall();
	}

	return EBTNodeResult::InProgress;
}
