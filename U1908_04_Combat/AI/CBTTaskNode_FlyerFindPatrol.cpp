// Fill out your copyright notice in the Description page of Project Settings.


#include "CBTTaskNode_FlyerFindPatrol.h"
#include "Global.h"
#include "CAIController.h"
#include "NavigationSystem.h"


UCBTTaskNode_FlyerFindPatrol::UCBTTaskNode_FlyerFindPatrol()
{
	NodeName = "Flyer Find Patrol";
}

EBTNodeResult::Type UCBTTaskNode_FlyerFindPatrol::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type type = Super::ExecuteTask(OwnerComp, NodeMemory);

	ACAIController* controller = Cast<ACAIController>(OwnerComp.GetAIOwner());
	RetNullResult(controller, EBTNodeResult::Failed);


	APawn* pawn = controller->GetPawn();
	RetNullResult(pawn, EBTNodeResult::Failed);

	UNavigationSystemV1* navSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());
	RetNullResult(navSystem, EBTNodeResult::Failed);
	FNavLocation location;
	//FVector origin = pawn->GetActorLocation();
	FVector origin = OwnerComp.GetBlackboardComponent()->GetValueAsVector("Home");
	
	OwnerComp.GetBlackboardComponent()->SetValueAsVector("Patrol", UKismetMathLibrary::RandomPointInBoundingBox(origin, FVector(500, 500, 0)));
	return EBTNodeResult::Succeeded;
}
