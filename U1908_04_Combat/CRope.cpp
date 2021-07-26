// Fill out your copyright notice in the Description page of Project Settings.


#include "CRope.h"
#include "MyGameProject/CParty.h"
#include "CCombatCharacter.h"
#include "Global.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "CableComponent.h"

// Sets default values
ACRope::ACRope()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	Cable = CreateDefaultSubobject<UCableComponent>(TEXT("Cable"));
	Cable->SetupAttachment(RootComponent);

	CableEnd = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CableEnd"));
	CableEnd->SetupAttachment(RootComponent);

	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	Capsule->SetupAttachment(CableEnd);

	PhysicsConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("PhysicsConstraint"));
	PhysicsConstraint->SetupAttachment(RootComponent);

	Cable->bAttachEnd = true;
	Cable->AttachEndTo.ComponentProperty = FName("CableEnd");
	Cable->EndLocation = FVector(0, 0, 0);
	Cable->CableLength = 500.0f;
	//Cable->SetSimulatePhysics(true);

	CableEnd->SetSimulatePhysics(true);
	CableEnd->SetWorldLocation(FVector(0, 0, -500));

	PhysicsConstraint->ComponentName1.ComponentName = FName("RootComponent");
	PhysicsConstraint->ComponentName2.ComponentName = FName("CableEnd");

	
	//
}

// Called when the game starts or when spawned
void ACRope::BeginPlay()
{
	Super::BeginPlay();
	//Capsule->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Capsule->OnComponentBeginOverlap.AddDynamic(this, &ACRope::IsGrabed);

}

// Called every frame
void ACRope::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACRope::IsGrabed(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	//if (OtherActor == this)return;
	//CLog::Print(TEXT("IsGrabed"));
	if (OtherActor->IsA(ACCombatCharacter::StaticClass()))
	{
		player = Cast<ACCombatCharacter>(OtherActor);
		player->OnGrabRope(this);
		//bGarbed = true;
	}
}

void ACRope::AddSwingforce(FVector force)
{
	//CLog::Print(TEXT("AddSwingforce"));
	CableEnd->AddForce(force, FName(), true);
}

