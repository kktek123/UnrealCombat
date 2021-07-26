// Fill out your copyright notice in the Description page of Project Settings.


#include "CDI_Hand.h"
#include "Global.h"
#include "MyGameProject/CParty.h"
#include "CCombatCharacter.h"
#include "CEnemy.h"

ACDI_Hand::ACDI_Hand(const class FObjectInitializer& ObjectInitializer)
{
	//Super::ACDisplayedItem(ObjectInitializer);
	WeaponMesh = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("StMesh"));
	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = WeaponMesh;

	Capsule = CreateDefaultSubobject<UCapsuleComponent>("Capsule");
	Capsule->SetupAttachment(WeaponMesh);

	FString path = L"StaticMesh'/Game/DynamicCombatSystem/Meshes/SM_GreatSword.SM_GreatSword'";
	ConstructorHelpers::FObjectFinder<UStaticMesh> mesh(*path);
	if (mesh.Succeeded())
		WeaponMesh->SetStaticMesh(mesh.Object);

	path = L"SoundWave'/Game/DynamicCombatSystem/SFX/WAV/WAV_Explosion02.WAV_Explosion02'";
	ConstructorHelpers::FObjectFinder<USoundBase> shoot(*path);
	if (shoot.Succeeded())
		BoomSound = shoot.Object;

	Capsule->SetRelativeLocation(FVector(0, 0, 80));
	Capsule->SetCapsuleRadius(10);
	Capsule->SetCapsuleHalfHeight(65);

	weaponType = E_WeaponType::Sword;

	ConstructorHelpers::FObjectFinder<UParticleSystem>particle
	(
		L"ParticleSystem'/Game/FXVarietyPack/Particles/P_ky_lightning3.P_ky_lightning3'"
	);
	if (particle.Succeeded())
		Particle = particle.Object;

}

void ACDI_Hand::OnBegin(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor == this)return;
	if (OtherActor == GetOwner())return;
	if (GetOwner()->IsA(ACEnemy::StaticClass()))
	{
		if (OtherActor->IsA(ACEnemy::StaticClass())) return;
	}
	if (GetOwner()->IsA(ACParty::StaticClass()))
	{
		if (OtherActor->IsA(ACParty::StaticClass())) return;
	}
	//OtherActor->Destroy();//네트워크
	UGameplayStatics::ApplyDamage(OtherActor, Power, NULL, GetOwner(), NULL);

}

void ACDI_Hand::OnEnd(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
}

void ACDI_Hand::BeginPlay()
{
	Super::BeginPlay();
	//if (IsValid(GetPrimaryComponent()))
	//{
	//	GetPrimaryComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	//}
	Capsule->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	Capsule->OnComponentBeginOverlap.AddDynamic(this, &ACDI_Hand::OnBegin);
	Capsule->OnComponentEndOverlap.AddDynamic(this, &ACDI_Hand::OnEnd);

}

void ACDI_Hand::OnHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if(IsValid(WeaponMesh))
	WeaponMesh->GetSocketLocation("Socket_06");

}

void ACDisplayedItem::Gen_Particle()
{
	FVector start;
	FVector end;
	if (IsValid(WeaponMesh))
	{
		start = WeaponMesh->GetSocketLocation("Socket_06");
		end = WeaponMesh->GetSocketLocation("Socket_06");
	}

	end.Z += Height;

	FCollisionShape sphere = FCollisionShape::MakeSphere(Radius);
	//DrawDebugSphere(GetWorld(), GetActorLocation(), sphere.GetSphereRadius(), 40, FColor::Green, true);
	//DrawDebugSphere(GetWorld(), start, sphere.GetSphereRadius(), 40, FColor::Green, false, 1);
	TArray<FHitResult>hits;


	bool bHit = GetWorld()->SweepMultiByChannel(hits, start, end, FQuat::Identity, ECC_WorldDynamic, sphere);
	TArray<AActor*>me;
	me.Add(this);

	if (bHit)
	{
		for (auto& hit : hits)
		{
			USkeletalMeshComponent* mesh = Cast<USkeletalMeshComponent>(hit.GetActor()->GetRootComponent());
			bool b = true;
			//b &= mesh != NULL;
			if(GetOwner()->IsA(ACParty::StaticClass()))
			b &= hit.GetActor()->IsA(ACParty::StaticClass()) == false;
			if (GetOwner()->IsA(ACEnemy::StaticClass()))
				b &= hit.GetActor()->IsA(ACEnemy::StaticClass()) == false;
			//b &= hit.GetActor()->IsA(ACEnemy::StaticClass()) == true;
			//b &= hit.GetActor()->GetName().Contains("Wall") == false;
			//b &= hit.GetActor()->GetName().Contains("FirstPersonCharacter") == false;

			if (b)
			{
				
				
				ACEnemy* enemy = Cast<ACEnemy>(hit.GetActor());
				float damage = 1;
				if (enemy->GetEnemyType() == E_EnemyType::Master)
					damage = 15;
				//UDamageType ud;
				UGameplayStatics::ApplyDamage(hit.GetActor(), Power*2, NULL, this, NULL);
				//UGameplayStatics::ApplyRadialDamage(GetWorld(), damage, GetActorLocation(),0,NULL,NULL,this);
				//if (hit.GetActor()->IsA(ACEnemy::StaticClass()))
				//{
				//	UGameplayStatics::ApplyRadialDamage(GetWorld(), 15, GetActorLocation(), 200.0f, NULL, me, this, NULL, true, ECC_Visibility);

				//}
			}
			//mesh->AddRadialImpulse(GetActorLocation(), Radius, mesh->GetMass()*1.25f, ERadialImpulseFalloff::RIF_Constant, true);//발산
		//force 충돌
		}
	}
	//Particle->Activate(true);
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Particle, start, FRotator());
	UGameplayStatics::PlaySoundAtLocation(this, BoomSound, start);
	bHit = false;
	//FlushPersistentDebugLines(GetWorld());
	//Destroy();
	
}

