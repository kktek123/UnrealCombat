// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CInverseKinemetics.h"
#include "Enums/CEnum0.h"
#include "CCombatAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class U1908_04_COMBAT_API UCCombatAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
protected:
	UPROPERTY(BlueprintReadOnly, Category = "Lean")
		float LeanAmount;

	UPROPERTY(BlueprintReadOnly, Category = "Lean")
		float LeanOffset;


	UPROPERTY(BlueprintReadOnly)
		float Speed;

	UPROPERTY(BlueprintReadOnly)
		bool bInAir;

	UPROPERTY(BlueprintReadOnly)
		bool bDrawing;

	UPROPERTY(BlueprintReadOnly)
		bool bSheathing;

	UPROPERTY(BlueprintReadOnly)
		float Direction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		FInverseKinemetics Effector;

	UPROPERTY(BlueprintReadOnly)
		E_State state;

	UPROPERTY(BlueprintReadOnly)
		E_CombatType combatType;

	UPROPERTY(BlueprintReadOnly)
		E_WeaponType weaponType;

	UPROPERTY(BlueprintReadOnly)
		bool activity;

	UPROPERTY(BlueprintReadOnly)
		bool bShieldEquipped;

	UPROPERTY(BlueprintReadOnly)
		float BlockAlpha;

	UPROPERTY(BlueprintReadOnly)
		float AimAlpha;

	UPROPERTY(BlueprintReadOnly)
		float MouseDeltaX;

	UPROPERTY(BlueprintReadOnly)
		float LocomotionRateScale = 1.0f;

	UPROPERTY(BlueprintReadOnly)
		float TurnThreshold = 0.2f;

	UPROPERTY(BlueprintReadOnly)
		float MinTurnLength = 0.9f;

	UPROPERTY(BlueprintReadOnly)
		float LookatYaw;

	UPROPERTY(BlueprintReadOnly)
		float LookatPitch;

	UPROPERTY(BlueprintReadOnly)
		bool IsLookingForward;

	UPROPERTY(BlueprintReadOnly)
		float AimOffsetAlpha;

	UPROPERTY(BlueprintReadOnly)
		bool bGrabRope;


		
public:
	UCCombatAnimInstance();

	void NativeBeginPlay() override;
	void NativeUpdateAnimation(float DeltaSeconds) override;

	void UpdateLeanAmount();
	void UpdateLookAtValues();
	void UpdateAimOffset();
private:
	class ACCombatCharacter* CombatPlayer;

	class UCInverseKinemetics * Foot;
};

