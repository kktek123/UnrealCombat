// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "UIRotate.generated.h"

// This class does not need to be modified.
UINTERFACE(Blueprintable)
class UUIRotate : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class U1908_04_COMBAT_API IUIRotate
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	//UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "GetDesiredRotation")
	virtual FRotator GetDesireRotation();
};
