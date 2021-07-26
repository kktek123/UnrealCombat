#include "CBTDecorator_CheckRange.h"
#include "Global.h"
#include "CAIController.h"

UCBTDecorator_CheckRange::UCBTDecorator_CheckRange()
{
	NodeName = "Check Attack";
	CheckInRange = 3000;
}

void UCBTDecorator_CheckRange::CheckTarget(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if(CalculateRawConditionValue(OwnerComp, NodeMemory))
	CheckInRange = 3000;
}

bool UCBTDecorator_CheckRange::CalculateRawConditionValue(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory) const
{
	Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	ACAIController* controller = Cast<ACAIController>(OwnerComp.GetAIOwner());
	RetNullResult(controller, false);

	APawn* pawn = controller->GetPawn();
	RetNullResult(pawn, false);

	APawn* target = Cast<APawn>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("Target"));
	RetNullResult(target, false);

	if (target->GetDistanceTo(pawn) <= CheckInRange)
	{
		return true;
	}

	return false;
}
