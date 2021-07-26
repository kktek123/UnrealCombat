// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CineCameraActor.h"
#include "DeadCineCameraActor.generated.h"

/**
 * 
 */
UCLASS()
class U1908_04_COMBAT_API ADeadCineCameraActor : public ACineCameraActor
{
	GENERATED_BODY()
public:
	ADeadCineCameraActor(const FObjectInitializer& ObjectInitializer);

	virtual void Tick(float DeltaTime) override;
	virtual bool ShouldTickIfViewportsOnly() const override;
	virtual void PostInitializeComponents() override;

protected:
	virtual void BeginPlay() override;
};
