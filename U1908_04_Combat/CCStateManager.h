#pragma once

#include "CoreMinimal.h"
#include "Enums/CEnum0.h"
#include "Components/ActorComponent.h"
#include "CCStateManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FStateChanged, E_State, PrevState, E_State, NewState);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FActivityChanged, E_Activity, Activity, bool, Value);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class U1908_04_COMBAT_API UCCStateManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCCStateManager();
	UFUNCTION()
		void SetState(E_State State);
	UFUNCTION()
		E_State GetState();
	UFUNCTION()
		void SetActivity(E_Activity Activity ,bool Value);
	UFUNCTION()
		bool GetActivityValue(E_Activity Activity);
	UFUNCTION()
		void ResetState(float InTime);

private:
	void SetIdleState();

public:
	E_State CurrentState;
	TMap<E_Activity, bool>Activities;
	TMap<E_Activity, float>intActivities;
public:
	UPROPERTY(BlueprintAssignable)
		FStateChanged OnStateChanged;
	UPROPERTY(BlueprintAssignable)
		FActivityChanged OnActivityChanged;

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

};
