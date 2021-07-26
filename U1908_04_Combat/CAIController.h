#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "CAIController.generated.h"

UCLASS()
class U1908_04_COMBAT_API ACAIController : public AAIController
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere)
		class UAIPerceptionComponent* Perception;

	UPROPERTY(VisibleAnywhere)
		class UAISenseConfig_Sight* Sight;

public:
	ACAIController();

	UPROPERTY(BlueprintReadWrite)
		AActor* GetTarget;

	class ACEnemy* PossesedAI;
protected:
	void BeginPlay() override;

	void OnPossess(APawn* InPawn) override;
	void OnUnPossess() override;

private:
	UFUNCTION()
		void OnSensingTarget(AActor* Actor, FAIStimulus Stimulus);

private:
	UPROPERTY(EditAnywhere)
	class UBehaviorTree* BT;
	class UBlackboardData* BB;


//private:
	//void OnRepeat();
	//FTimerHandle RepeatTimerHandle;
	//float RepeatInterval = 3.0f;
};
