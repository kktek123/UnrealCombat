// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "CMagicBoomAnimNotify.generated.h"

/**
 * 
 */
UCLASS()
class U1908_04_COMBAT_API UCMagicBoomAnimNotify : public UAnimNotify
{
	GENERATED_BODY()
public:
	void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

};
