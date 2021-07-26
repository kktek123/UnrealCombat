// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraActor.h"
#include "Enums/CEnum0.h"
#include "CCameraActor.generated.h"

/**
 * 
 */
UCLASS()
class U1908_04_COMBAT_API ACCameraActor : public ACameraActor
{
	GENERATED_BODY()
	
public:
	ACCameraActor();

	virtual void Tick(float DeltaSeconds);
	E_CameraSide GetCameraSide(){ return CameraSide; }
protected:
	//~ Begin AActor Interface
	virtual void BeginPlay() override;
	E_CameraSide CameraSide;

private:
	class ACCombatCharacter* player;
	//class ACharacter* player;
	class USpringArmComponent* PlayerCamera;


};
