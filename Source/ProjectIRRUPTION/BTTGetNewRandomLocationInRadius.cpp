// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTGetNewRandomLocationInRadius.h"

#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBTTGetNewRandomLocationInRadius::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	APawn* ControlledPawn = OwnerComp.GetAIOwner()->GetPawn();

	UNavigationSystemBase* NavigationSystemBase = GetWorld()->GetNavigationSystem();

	UNavigationSystemV1* NavigationSystemV1 = Cast<UNavigationSystemV1>(NavigationSystemBase);

	if(NavigationSystemV1)
	{
		FNavLocation NewLocation;
		FVector StartingLocation = OwnerComp.GetBlackboardComponent()->GetValueAsVector("StartingLocation");
		float radius = 300.0;
		
		bool success = NavigationSystemV1->GetRandomPointInNavigableRadius(StartingLocation, radius, NewLocation);

		if(success)
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsVector("NewLocation", NewLocation.Location);

			return EBTNodeResult::Succeeded;
		}
	}

	return EBTNodeResult::Failed;
}
