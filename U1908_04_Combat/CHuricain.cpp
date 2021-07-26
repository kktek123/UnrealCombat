// Fill out your copyright notice in the Description page of Project Settings.


#include "CHuricain.h"
#include "Global.h"
#include "CCombatCharacter.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
ACHuricain::ACHuricain()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ConstructorHelpers::FObjectFinder<UParticleSystem>particle
	(
		L"ParticleSystem'/Game/DynamicCombatSystem/VFX/P_FireballHit.P_FireballHit'"
	);
	if (particle.Succeeded())
		Particle = particle.Object;

	CollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("CapsuleComp"));
	CollisionComp->BodyInstance.SetCollisionProfileName("Collision");
	//CollisionComp->OnComponentHit.AddDynamic(this, &ACWindBlade::Explosion);		// set up a notification for when this component hits something blocking

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;
	RootComponent = CollisionComp;

	Huricain = CreateDefaultSubobject<UParticleSystemComponent>("Huricain");
	FString path = L"ParticleSystem'/Game/FXVarietyPack/Particles/P_ky_aquaStorm.P_ky_aquaStorm'";
	ConstructorHelpers::FObjectFinder<UParticleSystem> windBlade(*path);
	if (windBlade.Succeeded())
		Huricain->SetTemplate(windBlade.Object);
	Huricain->SetupAttachment(CollisionComp);

}

// Called when the game starts or when spawned
void ACHuricain::BeginPlay()
{
	Super::BeginPlay();
	//Capsule->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	CollisionComp->OnComponentHit.AddDynamic(this, &ACHuricain::OnHit);

	//CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &ACHuricain::OnBegin);
	//CollisionComp->OnComponentEndOverlap.AddDynamic(this, &ACHuricain::OnEnd);

}

// Called every frame
void ACHuricain::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACHuricain::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{
	if (OtherActor->IsA(ACCombatCharacter::StaticClass())) return;
	//UGameplayStatics::ApplyDamage(OtherActor, 30, NULL, GetOwner(), NULL);

}

void ACHuricain::OnBegin(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	//if (OtherActor == this)return;
	//if (OtherActor == GetOwner())return;
	if (OtherActor->IsA(ACCombatCharacter::StaticClass())) return;

	//OtherActor->Destroy();//네트워크
	//UGameplayStatics::ApplyDamage(OtherActor, 30, NULL, GetOwner(), NULL);

}

void ACHuricain::OnEnd(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
}

