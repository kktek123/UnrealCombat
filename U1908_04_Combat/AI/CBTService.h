// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enums/CEnum0.h"
#include "BehaviorTree/BTService.h"
#include "CBTService.generated.h"

/**
 * 
 */
UCLASS()
class U1908_04_COMBAT_API UCBTService : public UBTService
{
	GENERATED_BODY()
public:
	UCBTService();
protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	void ReceiveTickAI(AAIController* OwnerController, APawn* ControlledPawn, float DeltaSeconds);

	//UFUNCTION(BlueprintImplementableEvent, Category = AI)
	void ReceiveSearchStartAI(AAIController* OwnerController, APawn* ControlledPawn);
public:
	void OnStateChanged(E_State PrevState, E_State NewState);
	void OnStaminaValueChanged(float NewValue, float MaxValue);
	void Update(UBehaviorTreeComponent & OwnerComp);

	void UpdateBehavior(UBehaviorTreeComponent & OwnerComp);
	void UpdateActivities();
	FTimerHandle CountdownTimerHandle;

private:
	void SetBehavior(EC_AIBehavior Behavior);
	void Stamina();
public:
	UPROPERTY(EditAnywhere)
		FBlackboardKeySelector BehaviorKey;
	UPROPERTY(EditAnywhere)
		FBlackboardKeySelector TargetKey;
	class ACAIController* AOwnerController;
	class ACEnemy* ControlledCharacter;
	UPROPERTY(EditAnywhere)
		float AttackBehaviorRange;
	float TicksNearTarget;
	bool IsOutOfStamina;
	//AActor* Target;
	UBlackboardComponent* MyBlackboardComponent;
};

