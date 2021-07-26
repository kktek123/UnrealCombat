// Fill out your copyright notice in the Description page of Project Settings.


#include "CBTFly.h"
#include "Global.h"
#include "CEnemy.h"
#include "MyGameProject/CParty.h"
#include "CCombatCharacter.h"
#include "BehaviorTree/BTFunctionLibrary.h"
#include "CAIController.h"
#include "CCStateManager.h"
#include "CExtendedStamina.h"
#include "RotateComponent.h"

UCBTFly::UCBTFly()
{
	FleeBehaviorRange = 300;
}

void UCBTFly::TickNode(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	MyBlackboardComponent = OwnerComp.GetBlackboardComponent();

	ControlledCharacter = Cast<ACEnemy>(OwnerComp.GetAIOwner()->GetPawn());
	AOwnerController = Cast<ACAIController>((OwnerComp.GetAIOwner()));
	Update();
	ControlledCharacter->GetStateManager()->OnStateChanged.AddDynamic(this, &UCBTFly::OnStateChanged);
}

void UCBTFly::OnStateChanged(E_State PrevState, E_State NewState)
{
	if (PrevState == E_State::Disabled || NewState == E_State::Disabled || NewState == E_State::Attacking)
	{
		Update();
	}
}

void UCBTFly::Update()
{
	UpdateBehavior();
}

void UCBTFly::UpdateBehavior()
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
		ControlledCharacter->OnDead.AddLambda([&]()
		{
			//CLog::Print(FName("SetCamera"));
			//ACCombatCharacter* Player = Cast<ACCombatCharacter>(Target);
			//Player->SetCamera();
			//bAttacking = false;
		});
		return;
	}

	if (ControlledCharacter->GetStateManager()->GetState() == E_State::Disabled)
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

			if (IsFleeing)
			{
				SetBehavior(EC_AIBehavior::Flee);
			}
			else
			{
				//	CLog::Print(TEXT("NotBehindTarget"));
				if (StaminaPercent >= 80)
				{
					SetBehavior(EC_AIBehavior::RangeAttack);
				}
				else
				{
					if (DistanceToTarget >= 2000.0)
					{
						SetBehavior(EC_AIBehavior::Approach);
						//		CLog::Print(TEXT("Approach"));
					}
					else
					{
						SetBehavior(EC_AIBehavior::Patrol);
						//		CLog::Print(TEXT("StrafeAround"));
					}


				}//IsinAttackRange
			}//IsBehindTarget

		}//Check if target is set and if it's alive

	}//Check if controlled character's state is not disabled
	UpdateActivities();
}

void UCBTFly::UpdateActivities()
{
	RetNull(AOwnerController);
	RetNull(ControlledCharacter);
	EC_AIBehavior behavior = (EC_AIBehavior)MyBlackboardComponent->GetValueAsEnum("CBehavior");
	ACParty* Target = Cast<ACParty>(MyBlackboardComponent->GetValueAsObject("Target"));
	//EC_AIBehavior behavior = (EC_AIBehavior)UBTFunctionLibrary::GetBlackboardValueAsEnum(this, BehaviorKey);
	switch (behavior)
	{
	case EC_AIBehavior::Idle:
		ControlledCharacter->GetRotateComponent()->SetRotationMode(E_RotationMode::OrientToMovement);
		break;
		//CLog::Print(TEXT("Idle"));
	case EC_AIBehavior::Patrol:
		ControlledCharacter->GetRotateComponent()->SetRotationMode(E_RotationMode::OrientToMovement);
		break;
	case EC_AIBehavior::MeleeAttack:
		break;
	case EC_AIBehavior::RangeAttack:
		ControlledCharacter->GetRotateComponent()->SetRotationMode(E_RotationMode::FaceCamera);
		AOwnerController->SetFocus(Target);
		break;
	case EC_AIBehavior::Approach:
		ControlledCharacter->GetStateManager()->SetActivity(E_Activity::IsBlockingPressed, false);
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

void UCBTFly::Flee()
{
	//AOwnerController->TakeDamage();
}

void UCBTFly::SetBehavior(EC_AIBehavior Behavior)
{
	MyBlackboardComponent->SetValueAsEnum("CBehavior", (uint8)Behavior);

}
