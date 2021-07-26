// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "CameraChangeTrigger.generated.h"

/**
 * 
 */
UCLASS()
class U1908_04_COMBAT_API ACameraChangeTrigger : public ATriggerBox
{
	GENERATED_BODY()
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	// constructor sets default values for this actor's properties
	ACameraChangeTrigger();

	virtual void Tick(float DeltaSeconds);
	// overlap begin function
	UFUNCTION()
		void OnOverlapBegin(AActor* OverlappedActor,AActor* OtherActor);

	// overlap end function
	UFUNCTION()
		void OnOverlapEnd(AActor* OverlappedActor,AActor* OtherActor);

	UPROPERTY(EditAnywhere)
		class AActor* Camera;

	
	

	class AActor* GetCamera() { return Camera; }

private:
	class ACCombatCharacter* player;
	//class ACharacter* player;
	class USpringArmComponent* PlayerCamera;
//	class ACharacter* player;
	bool BoundPlayerToScreen;
	//AActor* Camera;
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class ACCameraActor> cameraclass;

};
