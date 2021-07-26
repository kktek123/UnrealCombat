// Fill out your copyright notice in the Description page of Project Settings.


#include "CImpactedArrow.h"
#include "Global.h"
// Sets default values
ACImpactedArrow::ACImpactedArrow()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Scene = CreateDefaultSubobject<UStaticMeshComponent>("Scene");
	RootComponent = Scene;
	ImpactedArrow = CreateDefaultSubobject<UStaticMeshComponent>("ImpactedArrow");
	ImpactedArrow->SetupAttachment(Scene);
	InitialLifeSpan = 3;
}

// Called when the game starts or when spawned
void ACImpactedArrow::BeginPlay()
{
	Super::BeginPlay();
	CLog::Print(TEXT("ACImpactedArrow"));

	//ImpactedArrow->SetStaticMesh(Arrow);



}

// Called every frame
void ACImpactedArrow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

