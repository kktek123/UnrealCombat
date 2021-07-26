#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CInverseKinemetics.h"
#include "CPlayerAnimInstance.generated.h"

UCLASS()
class U1908_04_COMBAT_API UCPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
protected:
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

public:
	UCPlayerAnimInstance();

	void NativeBeginPlay() override;
	void NativeUpdateAnimation(float DeltaSeconds) override;

private:
	class ACPlayer* Player;
	class UCInverseKinemetics* Foot;
};
