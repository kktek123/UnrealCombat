// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enums/CEnum0.h"
#include "Components/TimelineComponent.h"
#include "CGhostTrail.generated.h"

UCLASS()
class U1908_04_COMBAT_API ACGhostTrail : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACGhostTrail();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
		class UPoseableMeshComponent* PoseableMesh;

	FTimeline Opacity;
	float newOpacity;

	FTimerHandle CountdownTimerHandle;

	class ACCombatCharacter* PCR;

	TArray<UMaterialInstanceDynamic*> Dynamicmats;

	UPROPERTY(EditAnywhere)
		UMaterialInterface* M_GhostTrail;

	void GhostTrial();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION()
		void Progress(float Value);

	UFUNCTION()
		void ResetProgress();

	UFUNCTION()
		void UpdateProgress();


	UPROPERTY(EditAnywhere)
		class UCurveFloat* CurveFloat;


};
