// Fill out your copyright notice in the Description page of Project Settings.


#include "CBTTaskNode_Summon.h"
#include "Global.h"
#include "CEnemy.h"
#include "CAIController.h"

UCBTTaskNode_Summon::UCBTTaskNode_Summon()
{
	NodeName = "Summon";
}

EBTNodeResult::Type UCBTTaskNode_Summon::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	//enemy = Cast<ACEnemy>(OwnerComp.GetAIOwner()->GetPawn());
	//RetNullResult(enemy, EBTNodeResult::Failed);
	//enemy->BeginAttack();
	//bSummon = true;
	//enemy->OnEndAttack.AddLambda([&]()
	//{
	//	bSummon = false;
	//});

	//StartTime = 0;
	return EBTNodeResult::InProgress;

}

void UCBTTaskNode_Summon::TickTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	//StartTime += DeltaSeconds;
	//CLog::Print(DeltaSeconds, 0.1f, FColor::Green, 12);

		//if (enemy->GetState() != E_State::Attacking)
	//if (bSummon == false)
	//{
	//	//enemy->GetWorldTimerManager().SetTimer(CountdownTimerHandle, 2.0f, false);
	//	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	//}



}

void UCBTTaskNode_Summon::OnTaskFinished(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory, EBTNodeResult::Type TaskResult)
{
	Super::OnTaskFinished(OwnerComp, NodeMemory, TaskResult);

}
