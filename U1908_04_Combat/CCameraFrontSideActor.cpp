// Fill out your copyright notice in the Description page of Project Settings.

#include "CCameraFrontSideActor.h"
#include "CCombatCharacter.h"
#include "Global.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SceneComponent.h"

ACCameraFrontSideActor::ACCameraFrontSideActor(const class FObjectInitializer& Object)
{
	CameraSide = E_CameraSide::FrontSide;
}


void ACCameraFrontSideActor::Tick(float DeltaSeconds)
{
	//Super::Tick(DeltaSeconds);
	//if(UGameplayStatics::GetPlayerController(this, 0)->GetViewTarget() == this)

}

void ACCameraFrontSideActor::BeginPlay()
{
	//Super::BeginPlay();
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
