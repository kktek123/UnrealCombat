#include "CExtendedStamina.h"
#include "Global.h"
#include "CGameMode.h"

UCExtendedStamina::UCExtendedStamina()
{
	PrimaryComponentTick.bCanEverTick = true;
	CurrentValue = 100;
	TopValue = 100;
	RegenValue = 1;
	RegenableRegenTime = 0.5f;
	RegenerationTickInterval = 0.05;
}


void UCExtendedStamina::BeginPlay()
{
	Super::BeginPlay();
	InitStatManager();
	InitialRegenValue = RegenValue;
	SetCurrentValue(TopValue, false);
	RefreshRegenTimer();
	if (GetOwner() == (AActor*)UGameplayStatics::GetPlayerCharacter(this,0))
	{
		Cast<ACGameMode>(UGameplayStatics::GetGameMode(this));

	}
}


void UCExtendedStamina::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

//Event

void UCExtendedStamina::RefreshRegenTimer()
{
	//RegenHandle = UKismetSystemLibrary::K2_SetTimer(this, FString("UCExtendedStamina::StartRegenerating()"), RegenableRegenTime, false);

	if (DoesRegenerates)
	{
		if (!GetOwner()->GetWorldTimerManager().IsTimerActive(RegenHandle))
		{
			GetOwner()->GetWorldTimerManager().SetTimer(RegenHandle, this, &UCExtendedStamina::StartRegenerating, RegenableRegenTime, false);
		}


	}

}

void UCExtendedStamina::StartRegenerating()
{
	//RegenHandle = UKismetSystemLibrary::K2_SetTimer(this, FString("UCExtendedStamina::RegenTick()"), RegenerationTickInterval, true);
	GetOwner()->GetWorldTimerManager().SetTimer(RegenHandle, this, &UCExtendedStamina::RegenTick, RegenerationTickInterval, true);
}

void UCExtendedStamina::InitStatManager()
{
}

void UCExtendedStamina::OnGameLoaded()
{
	//Cast<ACGameMode>(UGameplayStatics::GetGameMode(this));

}

void UCExtendedStamina::OnModifierAdded(E_StatType Type, float Value)
{
	if (StatType == Type)
	{
		AddModifier(Value);
	}
}

void UCExtendedStamina::OnModifierRemoved(E_StatType Type, float Value)
{
	if (StatType == Type)
	{
		RemoveModifier(Value);
	}
}

void UCExtendedStamina::OnBaseValueChanged(E_StatType Type, float Value)
{
	if (StatType == Type)
	{
		TopValue = Value;
		OnValueChanged.Broadcast(CurrentValue, GetMaxValue());
	}
}

//function

void UCExtendedStamina::RegenTick()
{
	if (bSold)
	{
		ModifyStat(-SoldValue, false);
	}
	else if (CurrentValue < GetMaxValue())
	{
		ModifyStat(RegenValue, false);
		
	}
	else
	{
		ClearRegenTimer();
	}
}

void UCExtendedStamina::ClearRegenTimer()
{
	GetOwner()->GetWorldTimerManager().ClearTimer(RegenHandle);

}

void UCExtendedStamina::ChangeRegenPercent(int32 Percent)
{
	RegenValue = (float)Percent / 100 * InitialRegenValue;
}

void UCExtendedStamina::ModifyStat(float Value, bool InterruptRegeneration)
{
	if (Value != 0)
	{
		if (InterruptRegeneration == true)
		{
			ClearRegenTimer();
			DoesRegenerates = true;
		}
		SetCurrentValue(CurrentValue + Value,false);
		RefreshRegenTimer();
	}	
}

float UCExtendedStamina::GetCurrentValue()
{
	return CurrentValue;
}

float UCExtendedStamina::GetMaxValue()
{
	return TopValue + ModifierValue;
}

void UCExtendedStamina::AddModifier(float Value)
{
	ModifierValue = ModifierValue + Value;
	SetCurrentValue(UKismetMathLibrary::Clamp(CurrentValue, 0, GetMaxValue()), false);
	RefreshRegenTimer();
}

void UCExtendedStamina::RemoveModifier(float Value)
{
	ModifierValue = ModifierValue - Value;
	SetCurrentValue(UKismetMathLibrary::Clamp(CurrentValue, 0, GetMaxValue()), false);
	RefreshRegenTimer();

}

void UCExtendedStamina::SetCurrentValue(float Value, bool InterruptRegeneration)
{
	CurrentValue = UKismetMathLibrary::FClamp(Value, -100, GetMaxValue());
	OnValueChanged.Broadcast(CurrentValue, GetMaxValue());
	if (InterruptRegeneration == true)
	{
		ClearRegenTimer();
		RefreshRegenTimer();
	}
}

