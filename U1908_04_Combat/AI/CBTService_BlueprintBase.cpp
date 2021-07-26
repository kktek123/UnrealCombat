// Fill out your copyright notice in the Description page of Project Settings.


#include "CBTService_BlueprintBase.h"
#include "Global.h"
#include "CEnemy.h"
#include "BehaviorTree/BTFunctionLibrary.h"
#include "CAIController.h"

UCBTService_BlueprintBase::UCBTService_BlueprintBase()
{
	//CLog::Print(TEXT("GetSetvice"));
	AttackBehaviorRange = 500;
}

void UCBTService_BlueprintBase::TickNode(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory, float DeltaSeconds)
{
	ReceiveTickAI(OwnerComp.GetAIOwner(), OwnerComp.GetAIOwner()->GetPawn(), DeltaSeconds);
	ReceiveSearchStartAI(OwnerComp.GetAIOwner(), OwnerComp.GetAIOwner()->GetPawn());

}

void UCBTService_BlueprintBase::ReceiveTickAI(AAIController* OwnerController, APawn* ControlledPawn, float DeltaSeconds)
{
	//Super::ReceiveTickAI(OwnerController, ControlledPawn, DeltaSeconds);
	Update();
}


void UCBTService_BlueprintBase::ReceiveSearchStartAI(AAIController * OwnerController, APawn * ControlledPawn)
{
	//Super::ReceiveSearchStartAI(OwnerController, ControlledPawn);

	ControlledCharacter = Cast<ACEnemy>(ControlledPawn);
	AOwnerController = OwnerController;
	ControlledCharacter->GetStateManager()->OnStateChanged.AddDynamic(this, &UCBTService_BlueprintBase::OnStateChanged);
	ControlledCharacter->GetExtendedStamina()->OnValueChanged.AddDynamic(this, &UCBTService_BlueprintBase::OnStaminaValueChanged);

}

void UCBTService_BlueprintBase::OnStateChanged(E_State PrevState, E_State NewState)
{
	if (PrevState == E_State::Disabled || NewState == E_State::Disabled)
		Update();
}

void UCBTService_BlueprintBase::OnStaminaValueChanged(float NewValue, float MaxValue)
{
	if (NewValue <= 0)
	{
		IsOutOfStamina = true;
		ControlledCharacter->GetWorldTimerManager().SetTimer(CountdownTimerHandle,2.0f, IsOutOfStamina = false);

	}
}

void UCBTService_BlueprintBase::Update()
{
	CLog::Print(TEXT("AILoad"));
	UpdateBehavior();
	UpdateActivities();
}

void UCBTService_BlueprintBase::UpdateBehavior()
{
	RetNull(AOwnerController);
	RetNull(ControlledCharacter);
	float DistanceToTarget;
	AActor* Target;
	float DotProductToTarget;
	float StaminaPercent = 0;
	int32 ReceivedHisCount = 0;

	if (ControlledCharacter->GetStateManager()->GetState() == E_State::Disabled)
		SetBehavior(EC_AIBehavior::Hit);	
	else
	{
		Target = UBTFunctionLibrary::GetBlackboardValueAsActor(this, TargetKey);
		if (IsValid(Target))
		{
			DistanceToTarget = Target->GetDistanceTo(ControlledCharacter);
			DotProductToTarget = Target->GetDotProductTo(ControlledCharacter);

			StaminaPercent = ControlledCharacter->GetExtendedStamina()->GetCurrentValue()
				/ControlledCharacter->GetExtendedStamina()->GetMaxValue()
				* 100.0;

			if (DotProductToTarget <= -0.25)
			{
				if (DotProductToTarget <= AttackBehaviorRange)
					SetBehavior(EC_AIBehavior::MeleeAttack);
				else
					SetBehavior(EC_AIBehavior::Approach);

			}
			else
			{
				if (DotProductToTarget <= AttackBehaviorRange)
				{
					if (TicksNearTarget >= 3.0)
					{
						SetBehavior(EC_AIBehavior::MeleeAttack);
						if (UKismetMathLibrary::RandomBoolWithWeight(0.4))
							TicksNearTarget = 0;
					}
					else
					{
						TicksNearTarget = TicksNearTarget + 1;
						if (IsOutOfStamina || StaminaPercent <= 40.0 || UKismetMathLibrary::RandomBoolWithWeight(0.1))
							SetBehavior(EC_AIBehavior::MeleeAttack);
						else
						{
							SetBehavior(EC_AIBehavior::StrafeAround);
						}
					}
				}
				else
				{
					TicksNearTarget = 0;
					if (DistanceToTarget >= 200.0)
						SetBehavior(EC_AIBehavior::Approach);
					else							
						SetBehavior(EC_AIBehavior::StrafeAround);

				}//IsinAttackRange
			}//IsBehindTarget
				
		}//Check if target is set and if it's alive

	}//Check if controlled character's state is not disabled
}

void UCBTService_BlueprintBase::UpdateActivities()
{
	RetNull(AOwnerController);
	RetNull(ControlledCharacter);
	EC_AIBehavior behavior = (EC_AIBehavior)UBTFunctionLibrary::GetBlackboardValueAsEnum(this, BehaviorKey);
	switch (behavior)
	{
	case EC_AIBehavior::Idle:
		ControlledCharacter->GetStateManager()->SetActivity(E_Activity::IsBlockingPressed, false);
	case EC_AIBehavior::Patrol:
		ControlledCharacter->GetStateManager()->SetActivity(E_Activity::IsBlockingPressed, false);
	case EC_AIBehavior::MeleeAttack:
		ControlledCharacter->GetStateManager()->SetActivity(E_Activity::IsBlockingPressed, false);
	case EC_AIBehavior::RangeAttack:
		break;
	case EC_AIBehavior::Approach:
		ControlledCharacter->GetStateManager()->SetActivity(E_Activity::IsBlockingPressed, !IsOutOfStamina);
	case EC_AIBehavior::Flee:
		ControlledCharacter->GetStateManager()->SetActivity(E_Activity::IsBlockingPressed, false);
	case EC_AIBehavior::StrafeAround:
		ControlledCharacter->GetStateManager()->SetActivity(E_Activity::IsBlockingPressed, !IsOutOfStamina);
	case EC_AIBehavior::Hit:
		ControlledCharacter->GetStateManager()->SetActivity(E_Activity::IsBlockingPressed, false);
	default:
		break;
	}
	
}

void UCBTService_BlueprintBase::SetBehavior(EC_AIBehavior Behavior)
{
	UBTFunctionLibrary::SetBlackboardValueAsEnum(this, BehaviorKey, (uint8)Behavior);
}
