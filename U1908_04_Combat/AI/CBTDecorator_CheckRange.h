#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "CBTDecorator_CheckRange.generated.h"

UCLASS()
class U1908_04_COMBAT_API UCBTDecorator_CheckRange : public UBTDecorator
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
		float CheckInRange;

public:
	UCBTDecorator_CheckRange();
protected:
	bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;	
	void CheckTarget(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);

};
