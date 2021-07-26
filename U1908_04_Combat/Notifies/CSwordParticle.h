// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify_PlayParticleEffect.h"
#include "CSwordParticle.generated.h"

/**
 * 
 */
UCLASS()
class U1908_04_COMBAT_API UCSwordParticle : public UAnimNotify_PlayParticleEffect
{
	GENERATED_BODY()
public:
	void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
	
};
