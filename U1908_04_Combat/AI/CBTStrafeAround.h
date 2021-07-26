// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "EnvironmentQuery/EnvQuery.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "CBTStrafeAround.generated.h"
/**
 * 
 */
UCLASS()
class U1908_04_COMBAT_API UCBTStrafeAround : public UBTService
{
	GENERATED_BODY()
public:
	UCBTStrafeAround();
protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	void ReceiveTickAI(AAIController* OwnerController, APawn* ControlledPawn, float DeltaSeconds);

	//UFUNCTION(BlueprintImplementableEvent, Category = AI)
	void ReceiveDeactivationAI(AAIController* OwnerController, APawn* ControlledPawn);
	void ReceiveActivationAI(AAIController* OwnerController, APawn* ControlledPawn);
	void Strafe();
	void OnQueryFinished(FEnvQueryInstance* QueryInstance);

private:
	UFUNCTION(BlueprintPure)
		UEnvQuery* GetStrafeQuery();
	//UPROPERTY(EditInstanceOnly)
	//	FBlackboardKeySelector TargetKey;
	UPROPERTY(EditInstanceOnly)
		bool UseRandomDirection;
		UEnvQuery* QueryTemplate;
	APawn* AControlledPawn;
	APawn* TargetPawn;
	AAIController* AOwnerController;

	UPROPERTY(EditDefaultsOnly)
		class UEnvQuery* StrafeRight;
	UPROPERTY(EditDefaultsOnly)
		class UEnvQuery* StrafeLeft;
};
