// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerWidget.generated.h"

/**
 * 
 */
UCLASS()
class U1908_04_COMBAT_API UPlayerWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPlayerWidget(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;

	// Optionally override the tick event
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class ACCombatCharacter* player;

	UPROPERTY(BlueprintReadOnly)
		float Health;

	UPROPERTY(BlueprintReadOnly)
		float Stamina;

	UPROPERTY(BlueprintReadOnly)
		float Mage;


	class UWidgetCrosshair* GetCrosshair() { return Crosshair; }


	UPROPERTY(BlueprintReadWrite)
		class UWidgetCrosshair* Crosshair;

	UFUNCTION(BlueprintPure)
		float HealthBar();
	UFUNCTION(BlueprintPure)
		float StaminaBar();
	UFUNCTION(BlueprintPure)
		float ManaBar();


	UFUNCTION(BlueprintPure)
		ESlateVisibility bCrosshair();

private:
	class ACCombatCharacter* Player;


};
