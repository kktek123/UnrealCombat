// Fill out your copyright notice in the Description page of Project Settings.


#include "CBTBoss.h"
#include "Global.h"
#include "CEnemy.h"
#include "MyGameProject/CParty.h"
#include "CCombatCharacter.h"
#include "BehaviorTree/BTFunctionLibrary.h"
#include "CAIController.h"
#include "CCStateManager.h"
#include "CExtendedStamina.h"

UCBTBoss::UCBTBoss()
{
	StateBehaviorRange = 1000;
}

void UCBTBoss::TickNode(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	MyBlackboardComponent = OwnerComp.GetBlackboardComponent();

	ControlledCharacter = Cast<ACEnemy>(OwnerComp.GetAIOwner()->GetPawn());
	AOwnerController = Cast<ACAIController>((OwnerComp.GetAIOwner()));
	Update();
	ControlledCharacter->GetStateManager()->OnStateChanged.AddDynamic(this, &UCBTBoss::OnStateChanged);

}

void UCBTBoss::OnStateChanged(E_State PrevState, E_State NewState)
{
	if (PrevState == E_State::Disabled || NewState == E_State::Disabled || NewState == E_State::Attacking)
	{
		Update();
	}
}

void UCBTBoss::Update()
{
	UpdateBehavior();
}

void UCBTBoss::UpdateBehavior()
{
	float DistanceToTarget;
	float DotProductToTarget;
	float StaminaPercent;
	float HealthPercent;
	
	RetNull(ControlledCharacter);
	RetNull(AOwnerController);

	//int32 ReceivedHisCount;
	ACParty* Target = Cast<ACParty>(MyBlackboardComponent->GetValueAsObject("Target"));

	RetNull(Target);
	DistanceToTarget = Target->GetDistanceTo(ControlledCharacter);
	DotProductToTarget = Target->GetDotProductTo(ControlledCharacter);

	StaminaPercent = ControlledCharacter->GetExtendedStamina()->GetCurrentValue()
		/ ControlledCharacter->GetExtendedStamina()->GetMaxValue()
		* 100.0;

	HealthPercent = ControlledCharacter->GetExtendedHealth()->GetCurrentValue()
		/ ControlledCharacter->GetExtendedHealth()->GetMaxValue()
		* 100.0;

	if (ControlledCharacter->GetStateManager()->GetState() == E_State::Dead)
	{
		SetBehavior(EC_AIBehavior::Hit);
		ControlledCharacter->OnDead.AddLambda([&]()
		{
			//ACCombatCharacter* Player = Cast<ACCombatCharacter>(Target);
			//Player->SetCamera();
			//bAttacking = false;
		});
		return;
	}

	if (HealthPercent <= 70.0f && ControlledCharacter->SpawnedEnemyCount == 0)
	{
		SetBehavior(EC_AIBehavior::Summon);
		//CLog::Print(TEXT("Summon"));
	}
	else if (HealthPercent <= 40.0f && ControlledCharacter->SpawnedEnemyCount == 1)
	{
		SetBehavior(EC_AIBehavior::Summon);
		//CLog::Print(TEXT("Summon"));
	}
	else if (ControlledCharacter->GetStateManager()->GetState() == E_State::Disabled)
	{
		SetBehavior(EC_AIBehavior::Hit);
		//CLog::Print(FName("Hit"));
		//return;
	}
	else
	{

		//APawn* target = Cast<APawn>(ControlledCharacter.GetBlackboardComponent()->GetValueAsObject("Target1"));

		{



			if (DotProductToTarget <= -0.25)
			{
				if (DistanceToTarget <= StateBehaviorRange)
				{
					if (IsOutOfStamina || StaminaPercent <= 40.0 || UKismetMathLibrary::RandomBoolWithWeight(0.4))
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
					if (DistanceToTarget >= 1100)
					{
						SetBehavior(EC_AIBehavior::MeleeAttack);
						//		CLog::Print(TEXT("Approach"));
					}
					else
					{
						if (UKismetMathLibrary::RandomBoolWithWeight(0.7))
							SetBehavior(EC_AIBehavior::RangeAttack);
						else
							SetBehavior(EC_AIBehavior::MeleeAttack);
						//		CLog::Print(TEXT("StrafeAround"));
					}

				}

			}
			else
			{
				//	CLog::Print(TEXT("NotBehindTarget"));
				if (DistanceToTarget <= StateBehaviorRange)
				{

					if (TicksNearTarget >= 10.0)
					{
						//SetBehavior(EC_AIBehavior::MeleeAttack);
						//SetBehavior(EC_AIBehavior::MagicAttack);
						if (HealthPercent <= 70.0f && !bSpawnEnemy)
						{
							SetBehavior(EC_AIBehavior::Summon);
							bSpawnEnemy = true;
						}
						else
							SetBehavior(EC_AIBehavior::MagicAttack);
						//	CLog::Print(TEXT("MeleeAttack"));
						if (UKismetMathLibrary::RandomBoolWithWeight(0.4))
							TicksNearTarget = 0;
					}
					else
					{
						TicksNearTarget = TicksNearTarget + 1;
						if (IsOutOfStamina || StaminaPercent <= 40.0 || UKismetMathLibrary::RandomBoolWithWeight(0.4))
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
					TicksNearTarget = 0;
					if (DistanceToTarget >= 1100)
					{
						SetBehavior(EC_AIBehavior::MeleeAttack);
						//		CLog::Print(TEXT("Approach"));
					}
					else
					{
						if (UKismetMathLibrary::RandomBoolWithWeight(0.7))
							SetBehavior(EC_AIBehavior::RangeAttack);
						else
							SetBehavior(EC_AIBehavior::MeleeAttack);
						//		CLog::Print(TEXT("StrafeAround"));
					}


				}//IsinAttackRange
			}//IsBehindTarget

		}//Check if target is set and if it's alive

	}//Check if controlled character's state is not disabled
	UpdateActivities();
}

void UCBTBoss::UpdateActivities()
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
		break;
		//CLog::Print(TEXT("Idle"));
	case EC_AIBehavior::Patrol:
		ControlledCharacter->GetStateManager()->SetActivity(E_Activity::IsBlockingPressed, false);
		break;
	case EC_AIBehavior::MeleeAttack:
		ControlledCharacter->GetStateManager()->SetActivity(E_Activity::IsBlockingPressed, false);
		ControlledCharacter->GetStateManager()->SetActivity(E_Activity::IsAimingPressed, false);
		ControlledCharacter->SetCombatType(E_CombatType::Melee);
		AOwnerController->SetFocus(Target);
		break;
	case EC_AIBehavior::RangeAttack:
		ControlledCharacter->GetStateManager()->SetActivity(E_Activity::IsBlockingPressed, true);
		ControlledCharacter->GetStateManager()->SetActivity(E_Activity::IsAimingPressed, true);
		ControlledCharacter->SetCombatType(E_CombatType::Range);
		AOwnerController->SetFocus(Target);
		break;
	case EC_AIBehavior::MagicAttack:
		ControlledCharacter->GetStateManager()->SetActivity(E_Activity::IsBlockingPressed, false);
		ControlledCharacter->GetStateManager()->SetActivity(E_Activity::IsAimingPressed, false);
		ControlledCharacter->SetCombatType(E_CombatType::Magic);
		AOwnerController->ClearFocus(EAIFocusPriority::Gameplay);
		break;
	case EC_AIBehavior::Summon:
		ControlledCharacter->GetStateManager()->SetActivity(E_Activity::IsBlockingPressed, false);
		ControlledCharacter->GetStateManager()->SetActivity(E_Activity::IsAimingPressed, false);
		ControlledCharacter->SetCombatType(E_CombatType::Summon);
		AOwnerController->ClearFocus(EAIFocusPriority::Gameplay);
		break;
	case EC_AIBehavior::Approach:
		ControlledCharacter->GetStateManager()->SetActivity(E_Activity::IsBlockingPressed, false);
		break;
	case EC_AIBehavior::Flee:
		ControlledCharacter->GetStateManager()->SetActivity(E_Activity::IsBlockingPressed, false);
		ControlledCharacter->GetStateManager()->SetActivity(E_Activity::IsAimingPressed, false);
		break;
	case EC_AIBehavior::StrafeAround:
		ControlledCharacter->GetStateManager()->SetActivity(E_Activity::IsBlockingPressed, true);
		break;
	case EC_AIBehavior::Hit:
		ControlledCharacter->GetStateManager()->SetActivity(E_Activity::IsBlockingPressed, false);
		break;

		//default:
		//	break;
	}
}

void UCBTBoss::Flee()
{
}

void UCBTBoss::SetBehavior(EC_AIBehavior Behavior)
{
	MyBlackboardComponent->SetValueAsEnum("CBehavior", (uint8)Behavior);
}
