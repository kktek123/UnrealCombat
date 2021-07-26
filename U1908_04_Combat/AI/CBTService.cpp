// Fill out your copyright notice in the Description page of Project Settings.


#include "CBTService.h"
#include "Global.h"
#include "CEnemy.h"
#include "MyGameProject/CParty.h"
#include "CCombatCharacter.h"
#include "BehaviorTree/BTFunctionLibrary.h"
#include "CAIController.h"
#include "CCStateManager.h"
#include "CExtendedStamina.h"
#include "RotateComponent.h"

UCBTService::UCBTService()
{
	//CLog::Print(TEXT("GetSetvice"));
	AttackBehaviorRange = 500;
}

void UCBTService::TickNode(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	//ReceiveTickAI(OwnerComp.GetAIOwner(), OwnerComp.GetAIOwner()->GetPawn(), DeltaSeconds);

	MyBlackboardComponent = OwnerComp.GetBlackboardComponent();

	ControlledCharacter = Cast<ACEnemy>(OwnerComp.GetAIOwner()->GetPawn());
	AOwnerController = Cast<ACAIController>((OwnerComp.GetAIOwner()));
	Update(OwnerComp);
	ControlledCharacter->GetStateManager()->OnStateChanged.AddDynamic(this, &UCBTService::OnStateChanged);
	ControlledCharacter->GetExtendedStamina()->OnValueChanged.AddDynamic(this, &UCBTService::OnStaminaValueChanged);

	//ReceiveSearchStartAI(OwnerComp.GetAIOwner(), OwnerComp.GetAIOwner()->GetPawn());
}

void UCBTService::ReceiveTickAI(AAIController * OwnerController, APawn * ControlledPawn, float DeltaSeconds)
{
	ReceiveSearchStartAI(OwnerController, ControlledPawn);
	

}

void UCBTService::ReceiveSearchStartAI(AAIController * OwnerController, APawn * ControlledPawn)
{
	/*ControlledCharacter = Cast<ACEnemy>(ControlledPawn);
	AOwnerController = Cast<ACAIController>(OwnerController);*/

}

void UCBTService::OnStateChanged(E_State PrevState, E_State NewState)
{
//	if (PrevState == E_State::Disabled || NewState == E_State::Disabled)
		//Update();

}

void UCBTService::OnStaminaValueChanged(float NewValue, float MaxValue)
{
	//CLog::Print(TEXT("Change"));
	if (NewValue <= 0)
	{
		IsOutOfStamina = true;
		//CLog::Print(TEXT("Tired"));
		ControlledCharacter->GetWorldTimerManager().SetTimer(CountdownTimerHandle, 2.0f, IsOutOfStamina = false);

	}
}

void UCBTService::Update(UBehaviorTreeComponent & OwnerComp)
{
	UpdateBehavior(OwnerComp);
}

void UCBTService::UpdateBehavior(UBehaviorTreeComponent & OwnerComp)
{
	float DistanceToTarget;
	float DotProductToTarget;
	float StaminaPercent;
	RetNull(ControlledCharacter);
	RetNull(AOwnerController);

	//int32 ReceivedHisCount;
	ACParty* Target = Cast<ACParty>(MyBlackboardComponent->GetValueAsObject("Target"));
	if (ControlledCharacter->GetStateManager()->GetState() == E_State::Dead)
	{
		SetBehavior(EC_AIBehavior::Hit);
		AOwnerController->ClearFocus(EAIFocusPriority::Gameplay);
		ControlledCharacter->OnDead.AddLambda([&]()
		{
			//CLog::Print(FName("SetCamera"));
			//ACCombatCharacter* Player = Cast<ACCombatCharacter>(Target);
			//Player->SetCamera();
			//bAttacking = false;
		});
		return;
	}

	if (ControlledCharacter->GetStateManager()->GetState() == E_State::Damage || ControlledCharacter->GetStateManager()->GetState() == E_State::Stun)
	{
		SetBehavior(EC_AIBehavior::Hit);
		//CLog::Print(FName("Hit"));
		//return;
	}
	else
	{

		//APawn* target = Cast<APawn>(ControlledCharacter.GetBlackboardComponent()->GetValueAsObject("Target1"));
		RetNull(Target);
		{
			DistanceToTarget = Target->GetDistanceTo(ControlledCharacter);
			DotProductToTarget = Target->GetDotProductTo(ControlledCharacter);

			StaminaPercent = ControlledCharacter->GetExtendedStamina()->GetCurrentValue()
				/ ControlledCharacter->GetExtendedStamina()->GetMaxValue()
				* 100.0;

			if (StaminaPercent <= 0)
			{
				IsOutOfStamina = true;
				//CLog::Print(TEXT("Tired"));
				ControlledCharacter->GetWorldTimerManager().SetTimer(CountdownTimerHandle, this, &UCBTService::Stamina, 2.0f, false);

			}


			if (DotProductToTarget <= -0.25)
			{
				if (DistanceToTarget <= AttackBehaviorRange)
				{
					if (IsOutOfStamina || StaminaPercent <= 40.0 || UKismetMathLibrary::RandomBoolWithWeight(0.5))
					{
						SetBehavior(EC_AIBehavior::StrafeAround);
						//CLog::Print(TEXT("StrafeAround"));	
					}
					else
					{
						SetBehavior(EC_AIBehavior::MeleeAttack);
						//CLog::Print(TEXT("MeleeAttack"));
					}

				}
				else
				{
					SetBehavior(EC_AIBehavior::Approach);
			//		CLog::Print(TEXT("Approach"));

				}

			}
			else
			{
			//	CLog::Print(TEXT("NotBehindTarget"));
				if (DistanceToTarget <= AttackBehaviorRange)
				{
					if (TicksNearTarget >= 3.0)
					{
						SetBehavior(EC_AIBehavior::MeleeAttack);
					//	CLog::Print(TEXT("MeleeAttack"));
						if (UKismetMathLibrary::RandomBoolWithWeight(0.4))
							TicksNearTarget = 0;
					}
					else
					{
						TicksNearTarget = TicksNearTarget + 1;
						if (IsOutOfStamina || StaminaPercent <= 40.0 || UKismetMathLibrary::RandomBoolWithWeight(0.5))
						{
							SetBehavior(EC_AIBehavior::StrafeAround);
							//CLog::Print(TEXT("StrafeAround"));	
						}
						else
						{
							SetBehavior(EC_AIBehavior::MeleeAttack);
							//CLog::Print(TEXT("MeleeAttack"));
						}
					}
				}
				else
				{
					//CLog::Print(DistanceToTarget);
					TicksNearTarget = 0;
					if (DistanceToTarget >= 700.0)
					{
						SetBehavior(EC_AIBehavior::Approach);
					}
					else
					{
						SetBehavior(EC_AIBehavior::StrafeAround);
				//		CLog::Print(TEXT("StrafeAround"));
					}
						
					
				}//IsinAttackRange
			}//IsBehindTarget

		}//Check if target is set and if it's alive

	}//Check if controlled character's state is not disabled
	UpdateActivities();
}

void UCBTService::UpdateActivities()
{
	RetNull(AOwnerController);
	RetNull(ControlledCharacter);
	EC_AIBehavior behavior = (EC_AIBehavior)MyBlackboardComponent->GetValueAsEnum("CBehavior");
	ACParty* Target = Cast<ACParty>(MyBlackboardComponent->GetValueAsObject("Target"));
	//EC_AIBehavior behavior = (EC_AIBehavior)UBTFunctionLibrary::GetBlackboardValueAsEnum(this, BehaviorKey);
	switch (behavior)
	{
	case EC_AIBehavior::Idle:
		ControlledCharacter->GetStateManager()->SetActivity(E_Activity::IsBlockingPressed, true);
		//ControlledCharacter->GetRotateComponent()->SetRotationMode(E_RotationMode::OrientToMovement);
		break;
		//CLog::Print(TEXT("Idle"));
	case EC_AIBehavior::Patrol:
		ControlledCharacter->GetStateManager()->SetActivity(E_Activity::IsBlockingPressed, false);
		//ControlledCharacter->GetRotateComponent()->SetRotationMode(E_RotationMode::OrientToMovement);
		break;
	case EC_AIBehavior::MeleeAttack:
		ControlledCharacter->GetStateManager()->SetActivity(E_Activity::IsBlockingPressed, false);
		//ControlledCharacter->GetRotateComponent()->SetRotationMode(E_RotationMode::FaceCamera);
		ControlledCharacter->SetCombatType(E_CombatType::Melee);
		AOwnerController->SetFocus(Target);
		break;
	case EC_AIBehavior::RangeAttack:
		break;
	case EC_AIBehavior::Approach:
		ControlledCharacter->GetStateManager()->SetActivity(E_Activity::IsBlockingPressed, !IsOutOfStamina);
		AOwnerController->SetFocus(Target);
		break;
	case EC_AIBehavior::Flee:
		ControlledCharacter->GetStateManager()->SetActivity(E_Activity::IsBlockingPressed, false);
		break;
	case EC_AIBehavior::StrafeAround:
		ControlledCharacter->GetStateManager()->SetActivity(E_Activity::IsBlockingPressed, true);
		break;
	case EC_AIBehavior::Hit:
		ControlledCharacter->GetStateManager()->SetActivity(E_Activity::IsBlockingPressed, false);
		ControlledCharacter->GetRotateComponent()->SetRotationMode(E_RotationMode::OrientToMovement);
		AOwnerController->ClearFocus(EAIFocusPriority::Gameplay);
		break;
	//default:
	//	break;
	}


}

void UCBTService::SetBehavior(EC_AIBehavior Behavior)
{
	//UBTFunctionLibrary::SetBlackboardValueAsEnum(this, BehaviorKey, (uint8)Behavior);
	MyBlackboardComponent->SetValueAsEnum("CBehavior", (uint8)Behavior);
	//ControlledCharacter->GetBehavior = Behavior;
	//behavior = Behavior;
}

void UCBTService::Stamina()
{
	IsOutOfStamina = false;
}