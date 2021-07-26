// Fill out your copyright notice in the Description page of Project Settings.


#include "CFireStorm.h"
#include "Global.h"
#include "CCombatCharacter.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"



ACFireStorm::ACFireStorm()
{
	PrimaryActorTick.bCanEverTick = true;
	ConstructorHelpers::FObjectFinder<UParticleSystem>particle
	(
		L"ParticleSystem'/Game/DynamicCombatSystem/VFX/P_FireballHit.P_FireballHit'"
	);
	if (particle.Succeeded())
		Particle = particle.Object;

	CollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("CapsuleComp"));
	CollisionComp->BodyInstance.SetCollisionProfileName("FireStorm");
	//CollisionComp->OnComponentHit.AddDynamic(this, &ACWindBlade::Explosion);		// set up a notification for when this component hits something blocking

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;
	RootComponent = CollisionComp;

	FireStorm = CreateDefaultSubobject<UParticleSystemComponent>("Fireball");
	FString path = L"ParticleSystem'/Game/Explosions/FXVarietyPack/Particles/P_ky_fireStorm.P_ky_fireStorm'";
	ConstructorHelpers::FObjectFinder<UParticleSystem> windBlade(*path);
	if (windBlade.Succeeded())
		FireStorm->SetTemplate(windBlade.Object);
	FireStorm->SetupAttachment(CollisionComp);

	//ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	//ProjectileMovement->UpdatedComponent = CollisionComp;
	//ProjectileMovement->InitialSpeed = 300.f;
	//ProjectileMovement->MaxSpeed = 300.f;
	//ProjectileMovement->bRotationFollowsVelocity = true;
	//ProjectileMovement->bShouldBounce = true;
	CountdownTime = 1;
}

// Called when the game starts or when spawned
void ACFireStorm::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(CountdownTimerHandle, this, &ACFireStorm::AdvanceTimer, 1.0f, true);
	APlayerController* controller = GetWorld()->GetFirstPlayerController();
	APawn* pawn = controller->GetPawn();
	 location = pawn->GetActorLocation();
	 location.Z -= 50;
	 forward = pawn->GetActorForwardVector();
	 forward = forward * 10;
}

// Called every frame
void ACFireStorm::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	

	location.X += forward.X;
	location.Y += forward.Y;
	//location.Z += forward.Z;

	SetActorLocation(location);
	

}

void ACFireStorm::AdvanceTimer()
{
	--CountdownTime;
	if (CountdownTime < 1)
	{
		Destroy();

	}
}
