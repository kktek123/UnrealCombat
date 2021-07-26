// Fill out your copyright notice in the Description page of Project Settings.


#include "CBTStrafeAround.h"
#include "Global.h"
#include "AIController.h"
#include "EnvironmentQuery/EnvQueryManager.h"

UCBTStrafeAround::UCBTStrafeAround()
{
	FString path = L"EnvQuery'/Game/DynamicCombatSystem/Blueprints/AI/EQS/EQS_StrafeRight.EQS_StrafeRight'";
	ConstructorHelpers::FObjectFinder<UEnvQuery> right(*path);
	if (right.Succeeded())
		StrafeRight = right.Object;

	path = L"EnvQuery'/Game/DynamicCombatSystem/Blueprints/AI/EQS/EQS_StrafeLeft.EQS_StrafeLeft'";

	ConstructorHelpers::FObjectFinder<UEnvQuery> left(*path);
	if (left.Succeeded())
		StrafeLeft = left.Object;

}

void UCBTStrafeAround::TickNode(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory, float DeltaSeconds)
{
	ReceiveTickAI(OwnerComp.GetAIOwner(), OwnerComp.GetAIOwner()->GetPawn(), DeltaSeconds);
	ReceiveDeactivationAI(OwnerComp.GetAIOwner(), OwnerComp.GetAIOwner()->GetPawn());
	ReceiveActivationAI(OwnerComp.GetAIOwner(), OwnerComp.GetAIOwner()->GetPawn());

}

void UCBTStrafeAround::ReceiveTickAI(AAIController * OwnerController, APawn * ControlledPawn, float DeltaSeconds)
{
	Strafe();
}

void UCBTStrafeAround::ReceiveDeactivationAI(AAIController * OwnerController, APawn * ControlledPawn)
{
	OwnerController->ClearFocus(0);
	OwnerController->StopMovement();

	ControlledPawn->bUseControllerRotationYaw = false;
	//ControlledPawn->GetComponentByClass
}

void UCBTStrafeAround::ReceiveActivationAI(AAIController * OwnerController, APawn * ControlledPawn)
{
	AControlledPawn = ControlledPawn;
	AOwnerController = OwnerController;
	AOwnerController->SetFocus(TargetPawn,0);
	Strafe();
}

void UCBTStrafeAround::Strafe()
{
	UEnvQuery* EnvQuery;
	if (UseRandomDirection)
	{
		if (UKismetMathLibrary::RandomBool())
			EnvQuery = StrafeLeft;
		else
			EnvQuery= StrafeRight;
	}
	else
		EnvQuery = GetStrafeQuery();
	UEnvQueryManager::RunEQSQuery(GetWorld(), EnvQuery, AControlledPawn, EEnvQueryRunMode::RandomBest5Pct, NULL);

}	


void UCBTStrafeAround::OnQueryFinished(FEnvQueryInstance* QueryInstance)
{
	AOwnerController->MoveToLocation(QueryInstance->GetItemAsLocation(0), 20.0, false);
	
}

UEnvQuery * UCBTStrafeAround::GetStrafeQuery()
{
	IsValid(TargetPawn);
	float X, Y, Z;
	UKismetMathLibrary::BreakVector(TargetPawn->GetActorRightVector(),X,Y,Z);
	
	FVector a = UKismetMathLibrary::Normal(UKismetMathLibrary::MakeVector(X, Y, 0), 0.0001);
	
	UKismetMathLibrary::BreakVector(UKismetMathLibrary::GetDirectionUnitVector(TargetPawn->GetActorLocation(), AControlledPawn->GetActorLocation())
		, X, Y, Z);

	FVector b = UKismetMathLibrary::Normal(UKismetMathLibrary::MakeVector(X, Y, 0), 0.0001);

	if(UKismetMathLibrary::Dot_VectorVector(a, b)>=-0.01)
		return StrafeLeft;
	else
		return StrafeRight;

	
}



