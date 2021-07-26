// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "CMagicBoomAnimNotifyState.generated.h"

/**
 * 
 */
UCLASS()
class U1908_04_COMBAT_API UCMagicBoomAnimNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()
public:
	void NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration) override;
	void NotifyTick(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float FrameDeltaTime) override;
	void NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation) override;

};
