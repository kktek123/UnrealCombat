// Fill out your copyright notice in the Description page of Project Settings.


#include "CBTDecorator_CheckDecorater.h"
#include "Global.h"
#include "CAIController.h"
#include "CEnemy.h"

UCBTDecorator_CheckDecorater::UCBTDecorator_CheckDecorater()
{
	NodeName = "Check Attack";
}

bool UCBTDecorator_CheckDecorater::CalculateRawConditionValue(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory) const
{
	Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	//ACAIController* controller = Cast<ACAIController>(OwnerComp.GetAIOwner());
	ACEnemy* enemy = Cast<ACEnemy>(OwnerComp.GetAIOwner()->GetPawn());
	RetNullResult(enemy, false);
	if (enemy->GetState() == E_State::Dead)
		return false;
	//RetNullResult(controller, false);
	//APawn* pawn = controller->GetPawn();
	float CheckInRange;

	APawn* target = Cast<APawn>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("Target"));
	RetNullResult(target, false);


	if (enemy->GetEnemyType() == E_EnemyType::Pawn)
		CheckInRange = 200.0f;
	if (enemy->GetEnemyType() == E_EnemyType::Barghest)
		CheckInRange = 200.0f;
	if (enemy->GetEnemyType() == E_EnemyType::Warrok)
		CheckInRange = 500.0f;

	if (enemy->GetEnemyType() == E_EnemyType::Drangon)
		CheckInRange = 300.0f;

	//if (target->GetDistanceTo(enemy) <= CheckInRange)
	if ( UKismetMathLibrary::InRange_FloatFloat(target->GetDistanceTo(enemy),200,700,true,true))
		return true;

	return false;
}
