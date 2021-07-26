// Fill out your copyright notice in the Description page of Project Settings.


#include "EnvQueryContextLeft.h"
#include "Global.h"
#include "CEnemy.h"
#include "MyGameProject/CParty.h"
#include "CCombatCharacter.h"
#include "BehaviorTree/BTFunctionLibrary.h"
#include "CAIController.h"
#include "CCStateManager.h"
#include "CExtendedStamina.h"
#include "RotateComponent.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Actor.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Point.h"

void UEnvQueryContextLeft::ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const
{
	Super::ProvideContext(QueryInstance, ContextData);

	//Get the Owner of this Query and cast it to an actor
	//Then, get the actor's controller and cast to it our AIController
	//This code works for our case but avoid that many casts and one-liners in cpp.
	ACAIController* AICon = Cast<ACAIController>((Cast<AActor>((QueryInstance.Owner).Get())->GetInstigatorController()));

	if (AICon && AICon->GetTarget)
	{
		//Set the context SeeingPawn to the provided context data
		UEnvQueryItemType_Actor::SetContextHelper(ContextData, AICon->GetTarget);
	}
	AActor * QuerierActor = Cast<AActor>(QueryInstance.Owner.Get());
	
	FRotator Rotation = UKismetMathLibrary::FindLookAtRotation(QuerierActor->GetActorLocation(), AICon->GetTarget->GetActorLocation());
	FVector ResultingLocation = UKismetMathLibrary::Conv_RotatorToVector(UKismetMathLibrary::MakeRotator(0, 0, Rotation.Yaw - 90)) * 300 + QuerierActor->GetActorLocation();
	//CLog::Print(UKismetMathLibrary::Conv_RotatorToVector(UKismetMathLibrary::MakeRotator(0, 0, Rotation.Yaw - 90)).ToString());

	UEnvQueryItemType_Point::SetContextHelper(ContextData, ResultingLocation);
}

void UEnvQueryContextLeft::ProvideSingleLocation(UObject * QuerierObject, AActor * QuerierActor, FVector & ResultingLocation) const
{
}
