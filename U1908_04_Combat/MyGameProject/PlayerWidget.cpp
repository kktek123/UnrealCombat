// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerWidget.h"
#include "Global.h"
#include "CCombatCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "CCStateManager.h"
#include "CExtendedStamina.h"
#include "WidgetCrosshair.h"

UPlayerWidget::UPlayerWidget(const FObjectInitializer& ObjectInitializer)
	:Super::UUserWidget(ObjectInitializer)
{

}
void UPlayerWidget::NativeConstruct()
{
	player = Cast<ACCombatCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
}

void UPlayerWidget::NativeTick(const FGeometry & MyGeometry, float InDeltaTime)
{

}


float UPlayerWidget::HealthBar()
{
	if (IsValid(player))
	{
		float CurrentValue =
			player->GetExtendedHealth()->GetCurrentValue();
		float MaxValue =
			player->GetExtendedHealth()->GetMaxValue();
		return CurrentValue / MaxValue;
		
	}

	return 0;
}

float UPlayerWidget::StaminaBar()
{
	if (IsValid(player))
	{
		float CurrentValue =
			player->GetExtendedStamina()->GetCurrentValue();
		float MaxValue =
			player->GetExtendedStamina()->GetMaxValue();
		return CurrentValue / MaxValue;
	}
	return 0;
	
}

float UPlayerWidget::ManaBar()
{
	return 0.0f;
}

ESlateVisibility UPlayerWidget::bCrosshair()
{
	if (IsValid(player))
	{
		if (player->GetStateManager()->GetActivityValue(E_Activity::IsAimingPressed))
			return ESlateVisibility::Visible;
		else
			return ESlateVisibility::Hidden;


	}
	return ESlateVisibility::Hidden;
}



