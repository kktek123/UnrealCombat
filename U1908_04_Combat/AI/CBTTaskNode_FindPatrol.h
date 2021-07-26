// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "CBTTaskNode_FindPatrol.generated.h"

/**
 * 
 */
UCLASS()
class U1908_04_COMBAT_API UCBTTaskNode_FindPatrol : public UBTTaskNode
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere)
		float Distance = 1000.0f;
public:
	UCBTTaskNode_FindPatrol();
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
