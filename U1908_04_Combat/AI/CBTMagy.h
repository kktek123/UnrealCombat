// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enums/CEnum0.h"
#include "BehaviorTree/BTService.h"
#include "Components/TimelineComponent.h"
#include "CBTMagy.generated.h"

/**
 * 
 */
UCLASS()
class U1908_04_COMBAT_API UCBTMagy : public UBTService
{
	GENERATED_BODY()
public:
	UCBTMagy();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

public:
	void OnStateChanged(E_State PrevState, E_State NewState);
	void Update();

	void UpdateBehavior();
	void UpdateActivities();
	FTimerHandle CountdownTimerHandle;
private:
	void SetBehavior(EC_AIBehavior Behavior);
	bool bSpawnEnemy;
	bool bSpawnEnemy2;
	void Flee();
	void GetDamage();
public:
	UPROPERTY(EditAnywhere)
		FBlackboardKeySelector BehaviorKey;
	UPROPERTY(EditAnywhere)
		FBlackboardKeySelector TargetKey;
	class ACAIController* AOwnerController;
	class ACEnemy* ControlledCharacter;
	UPROPERTY(EditAnywhere)
		float StateBehaviorRange;
	UPROPERTY(EditAnywhere)
		float FleeBehaviorRange;
	bool IsFleeing;
	bool IsOutOfStamina;
	float TicksNearTarget;
	AActor* Target;
	UBlackboardComponent* MyBlackboardComponent;
	bool bfrist;

};
