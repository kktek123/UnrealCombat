// Fill out your copyright notice in the Description page of Project Settings.


#include "CBTTaskNode_Magic.h"
#include "Global.h"
#include "CEnemy.h"
#include "CAIController.h"

UCBTTaskNode_Magic::UCBTTaskNode_Magic()
{
	NodeName = "Magic";

	bNotifyTick = true;
}

EBTNodeResult::Type UCBTTaskNode_Magic::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	enemy = Cast<ACEnemy>(OwnerComp.GetAIOwner()->GetPawn());
	RetNullResult(enemy, EBTNodeResult::Failed);
	enemy->OnSpellIndicator(OwnerComp.GetBlackboardComponent()->GetValueAsVector("Target"));


	//StartTime = 0;
	return EBTNodeResult::InProgress;
}

void UCBTTaskNode_Magic::TickTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	//StartTime += DeltaSeconds;
	//CLog::Print(DeltaSeconds, 0.1f, FColor::Green, 12);

		//if (enemy->GetState() != E_State::Attacking)
	//if (bAttacking == false)
	//{
	//	//enemy->GetWorldTimerManager().SetTimer(CountdownTimerHandle, 2.0f, false);
	//	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	//}



}

void UCBTTaskNode_Magic::OnTaskFinished(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory, EBTNodeResult::Type TaskResult)
{
	Super::OnTaskFinished(OwnerComp, NodeMemory, TaskResult);

}


