// Fill out your copyright notice in the Description page of Project Settings.


#include "CFallRespawn.h"
#include "Global.h"
#include "CCombatCharacter.h"

// Sets default values
ACFallRespawn::ACFallRespawn()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	TransferVolume = CreateDefaultSubobject<USphereComponent>(TEXT("TransferVelume"));
	TransferVolume->SetCollisionProfileName(TEXT("OverlapOnlyPawn"));

	SpawnTransform = CreateDefaultSubobject<USceneComponent>(TEXT("SpawnTransform"));
}

// Called when the game starts or when spawned
void ACFallRespawn::BeginPlay()
{
	Super::BeginPlay();

	//TransferVolume->OnComponentBeginOverlap.(this, &ACFallRespawn::IsGrabed);

	
}

// Called every frame
void ACFallRespawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



void ACFallRespawn::NotifyActorBeginOverlap(AActor * OtherActor)
{

}

void ACFallRespawn::NotifyActorEndOverlap(AActor * OtherActor)
{
	if (OtherActor->IsA(ACCombatCharacter::StaticClass()))
	{
		Pawn = Cast<ACCombatCharacter>(OtherActor);

		if ((Pawn->fallpoint.GetLocation() - GetActorLocation()).Size() <= TransferVolume->GetScaledSphereRadius())
		{
			Pawn->FallRespawn = this;
			//CLog::Print((Pawn->fallpoint.GetLocation() - GetActorLocation()).Size());
		}
	}
}

void ACFallRespawn::IsGrabed(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	
	
}

void ACFallRespawn::Spawn()
{
	RetNull(Pawn);
	CLog::Print(TEXT("Spawn"));
	//CLog::Print(TransferVolume->GetScaledSphereRadius());
	//if ((Pawn->fallpoint.GetLocation() - GetActorLocation()).Size() <= TransferVolume->GetScaledSphereRadius())
	{
		Pawn->SetActorTransform(SpawnTransform->GetComponentToWorld());

	}
}