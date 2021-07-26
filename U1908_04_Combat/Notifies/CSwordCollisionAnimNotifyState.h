#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "CSwordCollisionAnimNotifyState.generated.h"

UCLASS()
class U1908_04_COMBAT_API UCSwordCollisionAnimNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()
	
public:
	void NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration) override;
	void NotifyTick(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float FrameDeltaTime) override;
	void NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation) override;
};