#include "CBTTaskNode_Attack.h"
#include "Global.h"
#include "CEnemy.h"
#include "CAIController.h"
UCBTTaskNode_Attack::UCBTTaskNode_Attack()
{
	NodeName = "Attack";

	bNotifyTick = true;
}

EBTNodeResult::Type UCBTTaskNode_Attack::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	enemy = Cast<ACEnemy>(OwnerComp.GetAIOwner()->GetPawn());
	RetNullResult(enemy, EBTNodeResult::Failed);
	enemy->BeginAttack();
	enemy->bHeavyAttack = UKismetMathLibrary::RandomBoolWithWeight(0.4f);
	bAttacking = true;
	enemy->OnEndAttack.AddLambda([&]()
	{
		bAttacking = false;
	});

	//StartTime = 0;
	return EBTNodeResult::InProgress;
}

void UCBTTaskNode_Attack::TickTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	//StartTime += DeltaSeconds;
	//CLog::Print(DeltaSeconds, 0.1f, FColor::Green, 12);

		//if (enemy->GetState() != E_State::Attacking)
	if (bAttacking == false)
	{
		//enemy->GetWorldTimerManager().SetTimer(CountdownTimerHandle, 2.0f, false);
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
	


}

void UCBTTaskNode_Attack::OnTaskFinished(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory, EBTNodeResult::Type TaskResult)
{
	Super::OnTaskFinished(OwnerComp, NodeMemory, TaskResult);

}
