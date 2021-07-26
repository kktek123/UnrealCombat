// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CCameraActor.h"
#include "CCameraUpSideActor.generated.h"

/**
 * 
 */
UCLASS()
class U1908_04_COMBAT_API ACCameraUpSideActor : public ACCameraActor
{
	GENERATED_BODY()
	
public:
	ACCameraUpSideActor(const class FObjectInitializer& Object);

	virtual void Tick(float DeltaSeconds);

protected:
	//~ Begin AActor Interface
	virtual void BeginPlay() override;

private:
	class ACCombatCharacter* player;
	//class ACharacter* player;
	class USpringArmComponent* PlayerCamera;


};
