// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "CBTTaskNode_Print.generated.h"

/**
 * 
 */
UCLASS()
class U1908_04_COMBAT_API UCBTTaskNode_Print : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UCBTTaskNode_Print();
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
