// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyGameProject/Item/CDisplayedItem.h"
#include "CDI_Bow.generated.h"

/**
 * 
 */
UCLASS()
class U1908_04_COMBAT_API ACDI_Bow : public ACDisplayedItem
{
	GENERATED_BODY()
	
public:
	ACDI_Bow(const class FObjectInitializer& Object);

	float GetAimAlpha() { return AimAlpha; }

private:
	FName HandAttachmentSocket;
};
