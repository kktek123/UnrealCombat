// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FireWall.generated.h"

UCLASS()
class U1908_04_COMBAT_API AFireWall : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFireWall();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
		class UBoxComponent* Wall;

	UPROPERTY(VisibleDefaultsOnly)
		class UParticleSystemComponent* FireWall;

	UPROPERTY(VisibleDefaultsOnly)
		class UParticleSystemComponent* FireWallEffect;
	void OnBlock();
	void OffBlock();
};
