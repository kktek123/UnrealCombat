// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "CRotateOwner.generated.h"

/**
 * 
 */
UCLASS()
class U1908_04_COMBAT_API UCRotateOwner : public UAnimNotifyState
{
	GENERATED_BODY()
		

public:
	UCRotateOwner();
	void NotifyTick(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float FrameDeltaTime) override;
	void NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration) override;
	void NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation) override;
	float MaxDegreesPerSecond = 720.0f;
	TSubclassOf<class URotateComponent> ComponentClass;
	class URotateComponent* RotateComponent;

};
