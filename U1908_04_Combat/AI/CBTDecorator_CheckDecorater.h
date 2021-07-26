// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "CBTDecorator_CheckDecorater.generated.h"

/**
 * 
 */
UCLASS()
class U1908_04_COMBAT_API UCBTDecorator_CheckDecorater : public UBTDecorator
{
	GENERATED_BODY()
private:
	//UPROPERTY(EditAnywhere)
		

public:
	UCBTDecorator_CheckDecorater();

protected:
	bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
