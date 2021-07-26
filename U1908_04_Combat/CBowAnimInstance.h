// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CBowAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class U1908_04_COMBAT_API UCBowAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UCBowAnimInstance();

	void NativeBeginPlay() override;
	void NativeUpdateAnimation(float DeltaSeconds) override;
protected:
	UPROPERTY(BlueprintReadOnly)
		float Speed;

	UPROPERTY(BlueprintReadOnly)
		float Direction;

	UPROPERTY(BlueprintReadOnly)
		float AimAlpha;

	UPROPERTY(BlueprintReadOnly)
		bool Blocking;


	UPROPERTY(BlueprintReadOnly)
		class UCCStateManager* StateManager;
public:



private:
	class ACDI_Bow* Item;


};
