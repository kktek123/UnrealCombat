// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CEnemyWidget.generated.h"

/**
 * 
 */
UCLASS()
class U1908_04_COMBAT_API UCEnemyWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UCEnemyWidget(const FObjectInitializer& ObjectInitializer);

	// Optionally override the Blueprint "Event Construct" event
	virtual void NativeConstruct() override;

	// Optionally override the tick event
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;;
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class ACEnemy* enemy;

	void SetEnemy(class ACEnemy* cenemy);

	UFUNCTION(BlueprintPure)
		float HealthBar();
	UFUNCTION(BlueprintPure)
		float StaminaBar();

	
};
