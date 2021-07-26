// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enums/CEnum0.h"
#include "BehaviorTree/BTService.h"
#include "CBTFly.generated.h"

/**
 * 
 */
UCLASS()
class U1908_04_COMBAT_API UCBTFly : public UBTService
{
	GENERATED_BODY()
public:
	UCBTFly();
protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

public:
	void OnStateChanged(E_State PrevState, E_State NewState);
	void Update();

	void UpdateBehavior();
	void UpdateActivities();
	FTimerHandle CountdownTimerHandle;
	void Flee();
private:
	void SetBehavior(EC_AIBehavior Behavior);

public:
	UPROPERTY(EditAnywhere)
		FBlackboardKeySelector BehaviorKey;
	UPROPERTY(EditAnywhere)
		FBlackboardKeySelector TargetKey;
	class ACAIController* AOwnerController;
	class ACEnemy* ControlledCharacter;
	UPROPERTY(EditAnywhere)
		float FleeBehaviorRange;
	bool IsFleeing;
	UBlackboardComponent* MyBlackboardComponent;

};
