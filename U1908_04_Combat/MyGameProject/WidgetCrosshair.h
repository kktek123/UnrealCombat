// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WidgetCrosshair.generated.h"

/**
 * 
 */
UCLASS()
class U1908_04_COMBAT_API UWidgetCrosshair : public UUserWidget
{
	GENERATED_BODY()
public:
	UWidgetCrosshair(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;

	// Optionally override the tick event
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;;

public:
	void SetCrosshairPosition(FVector WorldLocation);
	void SetCrosshairVisibility(bool visiblity);
	void SetCrosshairImage();
	FVector2D ScreenPosition;
	UPROPERTY(BlueprintReadWrite)
		class UImage* Crosshair;
};
