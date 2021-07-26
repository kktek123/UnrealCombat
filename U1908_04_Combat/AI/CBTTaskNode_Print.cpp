// Fill out your copyright notice in the Description page of Project Settings.


#include "CBTTaskNode_Print.h"
#include "Global.h"

UCBTTaskNode_Print::UCBTTaskNode_Print()
{
	NodeName = "Find print";
}

EBTNodeResult::Type UCBTTaskNode_Print::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type type = Super::ExecuteTask(OwnerComp, NodeMemory);

	AActor* actor = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("Target"));

	if (actor != NULL)
		CLog::Print(actor->GetName(),1,FColor::Blue,11);
	else
		CLog::Print(NULL);

	return EBTNodeResult::Succeeded;

}
