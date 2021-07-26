// Fill out your copyright notice in the Description page of Project Settings.

#include "CCameraUpSideActor.h"
#include "CCombatCharacter.h"
#include "Global.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SceneComponent.h"

ACCameraUpSideActor::ACCameraUpSideActor(const class FObjectInitializer& Object)
{
	CameraSide = E_CameraSide::UpSide;
}


void ACCameraUpSideActor::Tick(float DeltaSeconds)
{
//	Super::Tick(DeltaSeconds);
	//if(UGameplayStatics::GetPlayerController(this, 0)->GetViewTarget() == this)

}

void ACCameraUpSideActor::BeginPlay()
{
//	Super::BeginPlay();
	//player = Cast< ACCombatCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	//TArray<USceneComponent *> components;
	//player->GetComponents(components);

	//for (USceneComponent* comp : components)
	//{
	//	if (comp->IsA(USpringArmComponent::StaticClass()) == true)
	//		PlayerCamera = Cast<USpringArmComponent>(comp);
	//}

	//BoundPlayerToScreen = player->GetTest();
}
