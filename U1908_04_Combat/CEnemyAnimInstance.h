#pragma once

#include "CoreMinimal.h"
#include "Enums/CEnum0.h"
#include "Animation/AnimInstance.h"
#include "CEnemyAnimInstance.generated.h"

UCLASS()
class U1908_04_COMBAT_API UCEnemyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(BlueprintReadOnly)
		float Speed;

	UPROPERTY(BlueprintReadOnly)
		float Direction;

	UPROPERTY(BlueprintReadOnly)
		float AimAlpha;

	UPROPERTY(BlueprintReadOnly)
		E_State State;

	UPROPERTY(BlueprintReadOnly)
		E_Activity Activity;

	UPROPERTY(BlueprintReadOnly)
		bool Blocking;

	UPROPERTY(BlueprintReadOnly)
		E_EnemyType EnemyType;

	UPROPERTY(BlueprintReadOnly)
		class UCCStateManager* StateManager;
public:
	UCEnemyAnimInstance();

	void NativeBeginPlay() override;
	void NativeUpdateAnimation(float DeltaSeconds) override;

private:
	class ACEnemy* Enemy;

};
