// Fill out your copyright notice in the Description page of Project Settings.


#include "CDI_Shield.h"
#include "Global.h"

ACDI_Shield::ACDI_Shield(const class FObjectInitializer& ObjectInitializer)
{
	//Super::ACDisplayedItem(ObjectInitializer);
	WeaponMesh = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("StMesh"));
	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = WeaponMesh;

	Capsule = CreateDefaultSubobject<UCapsuleComponent>("Capsule");
	Capsule->SetupAttachment(WeaponMesh);

	FString path = L"StaticMesh'/Game/DynamicCombatSystem/Meshes/SM_SteelShield.SM_SteelShield'";
	ConstructorHelpers::FObjectFinder<UStaticMesh> mesh(*path);
	if (mesh.Succeeded())
		WeaponMesh->SetStaticMesh(mesh.Object);


	//Capsule->SetRelativeLocation(FVector(0, 0, 80));
	//Capsule->SetCapsuleRadius(10);
	//Capsule->SetCapsuleHalfHeight(65);

	weaponType = E_WeaponType::Shield;

}