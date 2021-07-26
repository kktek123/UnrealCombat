// Fill out your copyright notice in the Description page of Project Settings.


#include "CSpellIndicator.h"
#include "Global.h"


// Sets default values
ACSpellIndicator::ACSpellIndicator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//RootComponent = GetRootComponent();
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	Decal = CreateDefaultSubobject<UDecalComponent>(TEXT("Decal"));
	Decal->SetupAttachment(RootComponent);
	Decal->SetHiddenInGame(false);
}

// Called when the game starts or when spawned
void ACSpellIndicator::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACSpellIndicator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

