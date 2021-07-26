// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TimelineComponent.h"
#include "CBlockAlpha.generated.h"

UCLASS()
class U1908_04_COMBAT_API ACBlockAlpha : public AActor
{
	GENERATED_BODY()
	
private:
	UPROPERTY(VisibleAnywhere)
		class UCurveFloat* CurveFloat;

public:	
	ACBlockAlpha();

	class UCurveFloat* GetCurveFloat() { return CurveFloat; }
	FTimeline* GetTimeline() { return Timeline; }
private:
	void UpdateBlockTimeline(UCurveFloat* CurveFloat);


private:
	FTimeline* Timeline;

private:
	UFUNCTION()
		void Progress(float Value);

	UFUNCTION()
		void ResetProgress();

	class ACCombatCharacter* player;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
