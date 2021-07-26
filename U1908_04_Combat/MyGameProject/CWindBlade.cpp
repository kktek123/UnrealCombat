// Fill out your copyright notice in the Description page of Project Settings.


#include "CWindBlade.h"
#include "Global.h"
#include "CCombatCharacter.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

ACWindBlade::ACWindBlade()
{
	PrimaryActorTick.bCanEverTick = true;
	ConstructorHelpers::FObjectFinder<UParticleSystem>particle
	(
		L"ParticleSystem'/Game/DynamicCombatSystem/VFX/P_FireballHit.P_FireballHit'"
	);
	if (particle.Succeeded())
		Particle = particle.Object;

	CollisionComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComp"));
	CollisionComp->BodyInstance.SetCollisionProfileName("WindBlade");
	//CollisionComp->OnComponentHit.AddDynamic(this, &ACWindBlade::Explosion);		// set up a notification for when this component hits something blocking

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;
	RootComponent = CollisionComp;

	WindBlade = CreateDefaultSubobject<UParticleSystemComponent>("Fireball");
	FString path = L"ParticleSystem'/Game/VFX/P_SwordSpecial.P_SwordSpecial'";
	ConstructorHelpers::FObjectFinder<UParticleSystem> windBlade(*path);
	if (windBlade.Succeeded())
		WindBlade->SetTemplate(windBlade.Object);
	WindBlade->SetupAttachment(CollisionComp);
}

void ACWindBlade::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACWindBlade::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

