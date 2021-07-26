#pragma once

#include "CoreMinimal.h"
#include "Enums/CEnum0.h"
#include "Components/ActorComponent.h"
#include "CExtendedStamina.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FValueChanged, float, NewValue, float, MaxValue);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class U1908_04_COMBAT_API UCExtendedStamina : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCExtendedStamina();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void RefreshRegenTimer();
	void StartRegenerating();
	void InitStatManager();
	void OnGameLoaded();
	void OnModifierAdded(E_StatType Type, float Value);
	void OnModifierRemoved(E_StatType Type, float Value);
	void OnBaseValueChanged(E_StatType Type, float Value);

private:
	UFUNCTION(Category = "Regeneration")
		void RegenTick();
	UFUNCTION(Category = "Regeneration")
		void ClearRegenTimer();

public:
	UFUNCTION(Category = "Regeneration")
		void ChangeRegenPercent(int32 Percent);

	UFUNCTION(Category = "Stat")
		void ModifyStat(float Value, bool InterruptRegeneration);

	UFUNCTION(BlueprintPure, Category = "Stat")
		float GetCurrentValue();
	UFUNCTION(BlueprintPure, Category = "Stat")
		float GetMaxValue();

	UFUNCTION(Category = "Stat")
		void AddModifier(float Value);
	UFUNCTION(Category = "Stat")
		void RemoveModifier(float Value);
	UFUNCTION(Category = "Stat")
		void SetCurrentValue(float Value, bool InterruptRegeneration);

	UPROPERTY(EditAnywhere)
		E_StatType StatType;
	UPROPERTY(EditAnywhere)
		float RegenValue;
	UPROPERTY(EditAnywhere)
		float SoldValue;
	UPROPERTY(EditAnywhere)
		bool DoesRegenerates;
	UPROPERTY(EditAnywhere)
		float RegenableRegenTime;
	UPROPERTY(EditAnywhere)
		float RegenerationTickInterval;

	bool bSold;
private:
	UPROPERTY(EditDefaultsOnly)
		float CurrentValue;
	UPROPERTY(EditAnywhere)
		float TopValue;
	UPROPERTY(EditAnywhere)
		float ModifierValue;
	UPROPERTY()
		FTimerHandle RegenHandle;
	UPROPERTY(EditAnywhere)
		float InitialRegenValue;
public:
	UPROPERTY(BlueprintAssignable)
		FValueChanged OnValueChanged;
};
