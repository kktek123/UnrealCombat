// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "Components/TimelineComponent.h"
#include "CFlyingAIController.generated.h"

/**
 * 
 */
UCLASS()
class U1908_04_COMBAT_API ACFlyingAIController : public AAIController
{
	GENERATED_BODY()
	
private:
	UPROPERTY(VisibleAnywhere)
		class UAIPerceptionComponent* Perception;

	UPROPERTY(VisibleAnywhere)
		class UAISenseConfig_Sight* Sight;

public:
	ACFlyingAIController();

	UPROPERTY(BlueprintReadWrite)
		AActor* GetTarget;

	class ACEnemy* PossesedAI;
protected:
	void BeginPlay() override;

	void OnPossess(APawn* InPawn) override;
	void OnUnPossess() override;

public:
	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION()
		void OnSensingTarget(AActor* Actor, FAIStimulus Stimulus);
private:

	UFUNCTION()
		void Progress();

	UFUNCTION()
		void Progressfloat(float Value);


	UFUNCTION()
		void ResetProgress();

	UFUNCTION()
		void UpdateFlightTimeline(UCurveFloat* CurveFloat);
private:
public:
	UPROPERTY(EditAnywhere)
		class UBehaviorTree* BT;
	class UBlackboardData* BB;

	FTimeline Timeline;

	FVector NewLocation;
	FVector ML;
	FVector NL;

	UPROPERTY(EditAnywhere)
		class UCurveFloat* CurveFloat;

	void FindLocation();

	FOnTimelineEvent progress;
	FOnTimelineFloat progressfloat;
	FOnTimelineEvent timelineEvent;
};
