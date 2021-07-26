// Fill out your copyright notice in the Description page of Project Settings.


#include "CDI_Bow.h"
#include "Global.h"

ACDI_Bow::ACDI_Bow(const class FObjectInitializer& ObjectInitializer)
{
	//Super::ACDisplayedItem(ObjectInitializer);
	SkMesh = ObjectInitializer.CreateDefaultSubobject<USkeletalMeshComponent>(this, TEXT("SkMesh"));
	SkMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = SkMesh;

	FString path = L"SkeletalMesh'/Game/DynamicCombatSystem/Meshes/SK_ElvenBow.SK_ElvenBow'";
	ConstructorHelpers::FObjectFinder<USkeletalMesh> mesh(*path);
	if (mesh.Succeeded())
		SkMesh->SkeletalMesh = mesh.Object;

	weaponType = E_WeaponType::Bow;

	//Capsule->SetRelativeLocation(FVector(0, 0, 80));
	//Capsule->SetCapsuleRadius(10);
	//Capsule->SetCapsuleHalfHeight(65);
}


