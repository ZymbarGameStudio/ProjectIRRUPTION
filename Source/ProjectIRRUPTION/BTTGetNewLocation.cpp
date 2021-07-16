// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTGetNewLocation.h"

#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"


UBTTGetNewLocation::UBTTGetNewLocation()
{
	
}

EBTNodeResult::Type UBTTGetNewLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	FVector StartingLocation = OwnerComp.GetBlackboardComponent()->GetValueAsVector(TEXT("StartingLocation"));

	float radius = 500.0f;

	FNavLocation NewLocation;

	UNavigationSystemBase* NavSystemBase = GetWorld()->GetNavigationSystem();

	if(NavSystemBase)
	{
		UNavigationSystemV1* NavigationSystemV1 = Cast<UNavigationSystemV1>(NavSystemBase);

		if(NavigationSystemV1)
		{
			bool success = NavigationSystemV1->GetRandomPointInNavigableRadius(StartingLocation, radius, NewLocation);
			
			if(success)
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsVector(TEXT("NewLocation"), NewLocation.Location);

				return EBTNodeResult::Succeeded;
			}
		}
	}
			
	return EBTNodeResult::Failed;
}
