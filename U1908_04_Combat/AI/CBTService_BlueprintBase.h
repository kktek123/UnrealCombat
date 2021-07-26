// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enums/CEnum0.h"
#include "BehaviorTree/Services/BTService_BlueprintBase.h"
#include "CBTService_BlueprintBase.generated.h"

UCLASS()
class U1908_04_COMBAT_API UCBTService_BlueprintBase : public UBTService_BlueprintBase
{
	GENERATED_BODY()
	
public:
	UCBTService_BlueprintBase();
protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	//UFUNCTION(BlueprintImplementableEvent, Category = AI)
		void ReceiveTickAI(AAIController* OwnerController, APawn* ControlledPawn, float DeltaSeconds);
	
	//UFUNCTION(BlueprintImplementableEvent, Category = AI)
		void ReceiveSearchStartAI(AAIController* OwnerController, APawn* ControlledPawn);
public:
	void OnStateChanged(E_State PrevState,E_State NewState);
	void OnStaminaValueChanged(float NewValue,float MaxValue);
	void Update();

private:
	void UpdateBehavior();
	void UpdateActivities();
	FTimerHandle CountdownTimerHandle;

	void SetBehavior(EC_AIBehavior Behavior);

public:
	UPROPERTY(EditAnywhere)
		FBlackboardKeySelector BehaviorKey;
	UPROPERTY(EditAnywhere)
		FBlackboardKeySelector TargetKey;
	class AAIController* AOwnerController;
	class ACEnemy* ControlledCharacter;
	UPROPERTY(EditAnywhere)
		float AttackBehaviorRange;
	float TicksNearTarget;
	bool IsOutOfStamina;

};
