// Fill out your copyright notice in the Description page of Project Settings.


#include "CBTStrafe.h"
#include "Global.h"
#include "CEnemy.h"
#include "MyGameProject/CParty.h"
#include "CCombatCharacter.h"
#include "BehaviorTree/BTFunctionLibrary.h"
#include "CAIController.h"
#include "CCStateManager.h"
#include "CExtendedStamina.h"
#include "RotateComponent.h"



UCBTStrafe::UCBTStrafe()
{
	FString path = L"EnvQuery'/Game/DynamicCombatSystem/Blueprints/AI/EQS/EQS_StrafeRight.EQS_StrafeRight'";
	ConstructorHelpers::FObjectFinder<UEnvQuery> right(*path);
	if (right.Succeeded())
		RightQuery = right.Object;

	path = L"EnvQuery'/Game/DynamicCombatSystem/Blueprints/AI/EQS/EQS_StrafeLeft.EQS_StrafeLeft'";
	ConstructorHelpers::FObjectFinder<UEnvQuery> left(*path);
	if (left.Succeeded())
		LeftQuery = left.Object;
}

void UCBTStrafe::TickNode(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	MyBlackboardComponent = OwnerComp.GetBlackboardComponent();
	ControlledPawn = (OwnerComp.GetAIOwner()->GetPawn());
	AOwnerController = Cast<ACAIController>((OwnerComp.GetAIOwner()));

	AOwnerController->SetFocus(Cast<AActor>(MyBlackboardComponent->GetValueAsObject("Target")));
	Cast<ACEnemy>(ControlledPawn)->GetRotateComponent()->SetRotationMode(E_RotationMode::FaceCamera);
	Strafe();

	MyQueryRequest.Execute(EEnvQueryRunMode::RandomBest5Pct, this, &UCBTStrafe::OnQueryFinished);

}

void UCBTStrafe::OnQueryFinished(TSharedPtr<FEnvQueryResult> Result)
{
	//if (Result.IsValid())
	//{
	//	CLog::Print(Result->GetItemAsLocation(0).ToString());
	//	MyBlackboardComponent->SetValueAsVector("Patrol", Result->GetItemAsLocation(0));
	//	//AOwnerController->MoveToLocation(Result->GetItemAsLocation(0));

	//	//CLog::Print(Cast<AActor>(MyBlackboardComponent->GetValueAsObject("Target"))->GetActorLocation().ToString());
	//	////AOwnerController->MoveToLocation(FVector(10000,0,0));
	//	//MyBlackboardComponent->SetValueAsVector("Patrol", Cast<AActor>(MyBlackboardComponent->GetValueAsObject("Target"))->GetActorLocation());

	//}
	if (Result->IsSuccsessful()) {
		//CLog::Print(Result->GetItemAsLocation(0).ToString());
		MyBlackboardComponent->SetValueAsVector("Patrol", Result->GetItemAsLocation(0));
	}
	else
	{
		//CLog::Print(TEXT("StopMovement"));
		AOwnerController->StopMovement();
	}

	
}

FOnQueryFinshed UCBTStrafe::OnQueryFinished(UEnvQueryInstanceBlueprintWrapper* Result)
{
	if (IsValid(Result))
	{
		TArray<FVector> ResultLocations;
		if (Result->GetQueryResultsAsLocations(ResultLocations))
		{
			//CLog::Print(ResultLocations[0].ToString());
			MyBlackboardComponent->SetValueAsVector("Patrol", ResultLocations[0]);
		}

	}
	else
	{
		//CLog::Print(TEXT("StopMovement"));
		AOwnerController->StopMovement();
	}

	

	return FOnQueryFinshed();
}

void UCBTStrafe::Strafe()
{
	UEnvQuery* MyQuery;
	if (UseRandomDirection)
	{
		if (UKismetMathLibrary::RandomBool())
			MyQuery = RightQuery;
		else
			MyQuery = LeftQuery;
	}
	else
	{
		MyQuery = GetStrafeQuery();
	}
	//OnQueryFinished(UEnvQueryManager::RunEQSQuery(this, MyQuery, Cast<AActor>(ControlledPawn), EEnvQueryRunMode::RandomBest5Pct, TSubclassOf<UEnvQueryInstanceBlueprintWrapper>()));
	MyQueryRequest = FEnvQueryRequest(MyQuery, ControlledPawn);

}

UEnvQuery * UCBTStrafe::GetStrafeQuery()
{
	if (IsValid(MyBlackboardComponent->GetValueAsObject("Target")))
	{
		

		AActor* Value = Cast<AActor>(MyBlackboardComponent->GetValueAsObject("Target"));

		FVector UnitDir = UKismetMathLibrary::GetDirectionUnitVector(Value->GetActorLocation(), ControlledPawn->GetActorLocation());
		FVector ValueNormal = UKismetMathLibrary::Normal(FVector(UnitDir.X, UnitDir.Y, 0), 0.0001);
		FVector RightNormal = UKismetMathLibrary::Normal(FVector(Value->GetActorRightVector().X, Value->GetActorRightVector().Y, 0), 0.0001);
		float result = UKismetMathLibrary::Dot_VectorVector(ValueNormal, RightNormal);

		if (result >= -0.01)
		{
			//CLog::Print(LeftQuery->GetName());
			return LeftQuery;
		}
		else
		{
			//CLog::Print(RightQuery->GetName());
			return RightQuery;
		}
	}
	//CLog::Print(TEXT("nullptr"));
	return nullptr;
}
