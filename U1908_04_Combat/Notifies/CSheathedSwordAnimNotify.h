#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "CSheathedSwordAnimNotify.generated.h"

UCLASS()
class U1908_04_COMBAT_API UCSheathedSwordAnimNotify : public UAnimNotify
{
	GENERATED_BODY()
	
public:
	void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
