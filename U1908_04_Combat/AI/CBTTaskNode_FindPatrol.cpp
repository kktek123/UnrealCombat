// Fill out your copyright notice in the Description page of Project Settings.


#include "CBTTaskNode_FindPatrol.h"
#include "Global.h"
#include "CAIController.h"
#include "NavigationSystem.h"


UCBTTaskNode_FindPatrol::UCBTTaskNode_FindPatrol()
{
	NodeName = "Find Patrol";
}

EBTNodeResult::Type UCBTTaskNode_FindPatrol::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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

	if (navSystem->GetRandomPointInNavigableRadius(origin, Distance, location))//랜덤위치 이동
	{
		//CLog::Print(L"Test");
		OwnerComp.GetBlackboardComponent()->SetValueAsVector("Patrol", location.Location);
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}
