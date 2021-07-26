// Fill out your copyright notice in the Description page of Project Settings.


#include "FireWall.h"
#include "Global.h"

// Sets default values
AFireWall::AFireWall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Wall= CreateDefaultSubobject<UBoxComponent>(TEXT("Wall"));
	Wall->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = Wall;

	FireWall = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("FireWall"));
	FireWall->SetupAttachment(Wall);
	FireWall->SetHiddenInGame(true);

	FireWallEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("FireWallEffect"));
	FireWallEffect->SetupAttachment(Wall);

	FString path = L"ParticleSystem'/Game/InfinityBladeEffects/Effects/FX_Gates/Fire/P_Gate_Fire_Locked_01.P_Gate_Fire_Locked_01'";
	ConstructorHelpers::FObjectFinder<UParticleSystem> firewall(*path);
	if (firewall.Succeeded())
		FireWall->SetTemplate(firewall.Object);

	//path = L"ParticleSystem'/Game/InfinityBladeEffects/Effects/FX_Ambient/Fire/P_Env_Fire_Grate_01.P_Env_Fire_Grate_01'";
	//ConstructorHelpers::FObjectFinder<UParticleSystem> firewalleffect(*path);
	//if (firewalleffect.Succeeded())
	//	FireWallEffect->SetTemplate(firewalleffect.Object);
}

// Called when the game starts or when spawned
void AFireWall::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFireWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
}

void AFireWall::OnBlock()
{
	Wall->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	FireWall->SetHiddenInGame(false);
}

void AFireWall::OffBlock()
{
	Wall->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	FireWall->SetHiddenInGame(true);
}

