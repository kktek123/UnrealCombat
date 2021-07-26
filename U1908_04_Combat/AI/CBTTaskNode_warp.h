// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "CBTTaskNode_warp.generated.h"

/**
 * 
 */
UCLASS()
class U1908_04_COMBAT_API UCBTTaskNode_warp : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UCBTTaskNode_warp();

private:
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);

	ACEnemy* enemy;
	float StartTime = 0;
	bool bAttacking = false;
	FTimerHandle CountdownTimerHandle;

protected:
	void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	void OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult) override;


};
