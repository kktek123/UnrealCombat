// Fill out your copyright notice in the Description page of Project Settings.


#include "CEnemyWidget.h"
#include "Global.h"
#include "CEnemy.h"
#include "CExtendedStamina.h"

UCEnemyWidget::UCEnemyWidget(const FObjectInitializer& ObjectInitializer)
	:Super::UUserWidget(ObjectInitializer)
{

}

void UCEnemyWidget::NativeConstruct()
{
}

void UCEnemyWidget::NativeTick(const FGeometry & MyGeometry, float InDeltaTime)
{
}


void UCEnemyWidget::SetEnemy(ACEnemy * cenemy)
{
	enemy = cenemy;
}

float UCEnemyWidget::HealthBar()
{
	if (IsValid(enemy))
	{
		float CurrentValue =
			enemy->GetExtendedHealth()->GetCurrentValue();
		float MaxValue =
			enemy->GetExtendedHealth()->GetMaxValue();
		return CurrentValue / MaxValue;
	}
	return 0;
}

float UCEnemyWidget::StaminaBar()
{
	if (IsValid(enemy))
	{
		float CurrentValue =
			enemy->GetExtendedStamina()->GetCurrentValue();
		float MaxValue =
			enemy->GetExtendedStamina()->GetMaxValue();
		return CurrentValue / MaxValue;
	}
	return 0;
}
