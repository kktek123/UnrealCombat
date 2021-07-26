// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetCrosshair.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/Image.h"
#include "Components/CanvasPanelSlot.h"

UWidgetCrosshair::UWidgetCrosshair(const FObjectInitializer& ObjectInitializer)
	:Super::UUserWidget(ObjectInitializer)
{

}

void UWidgetCrosshair::NativeConstruct()
{
	SetCrosshairVisibility(false);
}

void UWidgetCrosshair::NativeTick(const FGeometry & MyGeometry, float InDeltaTime)
{
}

void UWidgetCrosshair::SetCrosshairPosition(FVector WorldLocation)
{
	if (UWidgetLayoutLibrary::ProjectWorldLocationToWidgetPosition(GetOwningPlayer(), WorldLocation, ScreenPosition))
		UWidgetLayoutLibrary::SlotAsCanvasSlot(Crosshair)->SetPosition(ScreenPosition);

}

void UWidgetCrosshair::SetCrosshairVisibility(bool visiblity)
{	
	if (visiblity)
		SetVisibility(ESlateVisibility::HitTestInvisible);
	else
		SetVisibility(ESlateVisibility::Hidden);
}

void UWidgetCrosshair::SetCrosshairImage()
{
}
