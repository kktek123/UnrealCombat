// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraChangeTrigger.h"
#include "CCombatCharacter.h"
#include "CCameraActor.h"
#include "Global.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SceneComponent.h"

ACameraChangeTrigger::ACameraChangeTrigger()
{
	OnActorBeginOverlap.AddDynamic(this, &ACameraChangeTrigger::OnOverlapBegin);
	OnActorEndOverlap.AddDynamic(this, &ACameraChangeTrigger::OnOverlapEnd);

	//FString path = L"Blueprint'/Game/MyPortpol/Player/CombatChracter.CombatChracter_C'";
	//ConstructorHelpers::FClassFinder<ACCombatCharacter> arrow(*path);
	//if (arrow.Succeeded())
	//	player = arrow.Class;

	//FString path = L"Blueprint'/Game/MyCCameraActor.MyCCameraActor_C'";
	//ConstructorHelpers::FClassFinder<ACCameraActor> arrow(*path);
	//if (arrow.Succeeded())
	//	cameraclass = arrow.Class;
	//Camera->AttachToActor(GetOwner(),FAttachmentTransformRules::KeepWorldTransform);


}

void ACameraChangeTrigger::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);


}

void ACameraChangeTrigger::BeginPlay()
{
	Super::BeginPlay();

	//BoundPlayerToScreen = player->GetTest();

	FTransform transform = FTransform::Identity;
	FActorSpawnParameters params;
	params.Owner = this;
	player = Cast< ACCombatCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	TArray<USceneComponent *> components;
	player->GetComponents(components);

	for (USceneComponent* comp : components)
	{
		if (comp->IsA(USpringArmComponent::StaticClass()) == true)
			PlayerCamera = Cast<USpringArmComponent>(comp);
	}

	BoundPlayerToScreen = player->GetTest();
	//if (IsValid(cameraclass))
	//	Camera = GetWorld()->SpawnActor<ACCameraActor>(cameraclass, transform, params);

}

void ACameraChangeTrigger::OnOverlapBegin(AActor * OverlappedActor, AActor * OtherActor)
{
	if (OtherActor && (OtherActor != this))
	{
		player = Cast<ACCombatCharacter>(OtherActor);
		//RetNull(player)
		//RetNull(Camera);
		UGameplayStatics::GetPlayerController(this, 0)->SetViewTargetWithBlend(Camera, 0.75);
		//if(BoundPlayerToScreen == false)
		//	Camera->AttachToComponent(PlayerCamera, FAttachmentTransformRules::KeepWorldTransform);		//
		//else if(BoundPlayerToScreen == true)
		//	Camera->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

	}
}

void ACameraChangeTrigger::OnOverlapEnd(AActor * OverlappedActor, AActor * OtherActor)
{
	if (OtherActor && (OtherActor != this))
	{
		player = Cast<ACCombatCharacter>(OtherActor);

		//Camera->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	}
}
