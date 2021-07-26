// Fill out your copyright notice in the Description page of Project Settings.


#include "CDisplayedItem.h"
#include "MyGameProject/CParty.h"
#include "CCombatCharacter.h"
#include "Global.h"

ACDisplayedItem::ACDisplayedItem()
{

}

ACDisplayedItem::ACDisplayedItem(const class FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;//매프래임마다 호출

	//WeaponMesh = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this , TEXT("Mesh"));
	//WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	//RootComponent = WeaponMesh;
}


void ACDisplayedItem::SetOwningPawn(class ACParty * NewOwner)
{
	if (MyPawn != NewOwner)
	{
		MyPawn = Cast<ACCombatCharacter>(NewOwner);
		//MyPawn = NewOwner;
	}
}

void ACDisplayedItem::AttachMeshToPawn()
{
	if (MyPawn)
	{
		USkeletalMeshComponent* PawnMesh = MyPawn->GetSpecificPawnMesh();
		FName AttachPoint;
		if (IsValid(WeaponMesh))
		{
			AttachPoint = MyPawn->GetSwordAttachPoint();
			WeaponMesh->AttachToComponent(PawnMesh, FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), AttachPoint);
		}
		if (IsValid(SkMesh))
		{
			//SkMesh->SetHiddenInGame(false);
			AttachPoint = MyPawn->GetBowAttachPoint();
			SkMesh->AttachToComponent(PawnMesh, FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), AttachPoint);
		}
		else if (IsValid(Magic))
		{
			//Particle->SetHiddenInGame(false);
			AttachPoint = MyPawn->GetSpellAttachPoint();
			Magic->AttachToComponent(PawnMesh, FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), AttachPoint);
		}
	}
}

void ACDisplayedItem::OnEquip(const ACDisplayedItem * LastWeapomn)
{
	AttachMeshToPawn();
}

void ACDisplayedItem::OnUnEquip()
{
	USkeletalMeshComponent* PawnMesh = MyPawn->GetSpecificPawnMesh();
	FName AttachPoint;
	if (IsValid(WeaponMesh))
	{
		AttachPoint = MyPawn->GetSwordAttachPoint();
		WeaponMesh->AttachToComponent(PawnMesh, FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), AttachPoint);
	}
	if (IsValid(SkMesh))
	{
		//SkMesh->SetHiddenInGame(true);
		AttachPoint = MyPawn->GetBowAttachPoint();
		SkMesh->AttachToComponent(PawnMesh, FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), AttachPoint);
	}
	if (IsValid(Magic))
	{
		ChangeSpell();
	}
}

//void ACDisplayedItem::OnBegin(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
//{
//}
//
//void ACDisplayedItem::OnEnd(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
//{
//}



//UPrimitiveComponent* ACDisplayedItem::GetPrimaryComponent()
//{
//	UActorComponent* Actor = GetOwner()->GetComponentByClass(USkeletalMeshComponent::StaticClass());
//	UPrimitiveComponent* Component = Cast<UPrimitiveComponent>(Actor);
//	if(IsValid(Component) == true)
//		return Component;
//	else
//	{
//		Actor = GetOwner()->GetComponentByClass(UStaticMeshComponent::StaticClass());
//		Component = Cast<UPrimitiveComponent>(Actor);
//		if (IsValid(Component) == true)
//			return Component;
//		else
//		{
//			Actor = GetOwner()->GetComponentByClass(UParticleSystem::StaticClass());
//			Component = Cast<UPrimitiveComponent>(Actor);
//			return Component;
//		}
//
//	}
//}

//bool ACDisplayedItem::Attach()
//{
//	UPrimitiveComponent* LMeshComponent = GetPrimaryComponent();
//	if (IsValid(LMeshComponent) == false)
//		return false;
//	else
//	{
//		LMeshComponent->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), GetAttachmentSocket());
//		return true;
//	}
//}

//FName ACDisplayedItem::GetAttachmentSocket()
//{
//
//	AttachmentSocket = "sword";
//	return AttachmentSocket;
//}
//
//void ACDisplayedItem::SimulatePhysics()
//{
//}

void ACDisplayedItem::BeginPlay()
{
	Super::BeginPlay();
	//if (IsValid(GetPrimaryComponent()))
	//{
	//	GetPrimaryComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	//}
}

void ACDisplayedItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACDisplayedItem::SetAimAlpha(float f)
{
	AimAlpha = f;
}
