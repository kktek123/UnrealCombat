// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "EnvironmentQuery/EnvQuery.h"
#include "EnvironmentQuery/EnvQueryManager.h"
#include "CBTStrafe.generated.h"

/**
 * 
 */
DECLARE_MULTICAST_DELEGATE(FOnQueryFinshed)

UCLASS()
class U1908_04_COMBAT_API UCBTStrafe : public UBTService
{
	GENERATED_BODY()
public:
	UCBTStrafe();
protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
	void OnQueryFinished(TSharedPtr<FEnvQueryResult> Result);

	FOnQueryFinshed OnQueryFinished(UEnvQueryInstanceBlueprintWrapper* Result);
	void Strafe();

public:
	UFUNCTION(BlueprintPure)
		class UEnvQuery* GetStrafeQuery();
public:
	UPROPERTY(EditAnywhere)
		FBlackboardKeySelector TargetKey;
	UPROPERTY(EditAnywhere)
		bool UseRandomDirection;

	UBlackboardComponent* MyBlackboardComponent;
private:
	FEnvQueryRequest MyQueryRequest;
	
	class UEnvQuery* QueryTemplate;
	APawn* ControlledPawn;
	class ACAIController* AOwnerController;
	class UEnvQuery* RightQuery;
	class UEnvQuery* LeftQuery;

};
