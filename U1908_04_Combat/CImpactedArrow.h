// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CImpactedArrow.generated.h"

UCLASS()
class U1908_04_COMBAT_API ACImpactedArrow : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACImpactedArrow();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleDefaultsOnly)
		class UStaticMeshComponent* ImpactedArrow;

	UPROPERTY(EditAnywhere)
		class UStaticMesh* Arrow;

	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* Scene;

	UPROPERTY(EditAnywhere)
		float LifeTime;
};
