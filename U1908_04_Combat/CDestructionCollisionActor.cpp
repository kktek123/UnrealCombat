// Fill out your copyright notice in the Description page of Project Settings.


#include "CDestructionCollisionActor.h"
#include "Global.h"
#include "CCombatCharacter.h"
#include "CEnemy.h"
#include "Components/SphereComponent.h"

// Sets default values
ACDestructionCollisionActor::ACDestructionCollisionActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComp"));
	TriggerComp = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerComp"));
	TriggerComp->SetupAttachment(RootComponent);
	Totam = CreateDefaultSubobject<UDestructibleComponent>(TEXT("Totam"));
	Totam->SetupAttachment(RootComponent);
	Totam->SetNotifyRigidBodyCollision(true);


	FString path = L"SoundCue'/Game/SFX/CUE/CUE_GroundExplosion.CUE_GroundExplosion'";
	ConstructorHelpers::FObjectFinder<USoundBase> pain(*path);
	if (pain.Succeeded())
		DestructSound = pain.Object;
	//MaxHealth = 1.0f;

	//DefaultDamage = 1.0f;
	//DefaultImpulse = 1.0f;

	TriggerComp->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel2, ECollisionResponse::ECR_Overlap);

}

// Called when the game starts or when spawned
void ACDestructionCollisionActor::BeginPlay()
{
	Super::BeginPlay();
	TriggerComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Totam->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	CurrentHealth = MaxHealth;
	TriggerComp->OnComponentHit.AddDynamic(this, &ACDestructionCollisionActor::OnHit);
	//TriggerComp->OnComponentBeginOverlap.AddDynamic(this, &ACDestructionCollisionActor::OnBegin);
	//TriggerComp->OnComponentEndOverlap.AddDynamic(this, &ACDestructionCollisionActor::OnEnd);

}

// Called every frame
void ACDestructionCollisionActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float ACDestructionCollisionActor::TakeDamage(float Damage, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	CurrentHealth -= 0.1;


	if (CurrentHealth <= 0)
	{
		if (!IsDestroyed)
		{
			if (CurrentHealth <= 0 && !bDestruction)
			{
				bDestruction = true;
				Destruction();
				//Totam->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
				Totam->ApplyRadiusDamage(DefaultDamage, GetActorLocation(), 1, DefaultImpulse, true);

			}
		}
	}

	return Damage;
}

void ACDestructionCollisionActor::OnHit(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{
	if (OtherActor->IsA(ACEnemy::StaticClass()))
	{
		colpawn = Cast<ACEnemy>(OtherActor);
		if (colpawn->GetEnemyType() == E_EnemyType::Master)
		{
			CurrentHealth -= 3;
			if (CurrentHealth <= 0 && !bDestruction)
			{
				bDestruction = true;
				Destruction();
				//Totam->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

				Totam->ApplyRadiusDamage(DefaultDamage, GetActorLocation(), 1, DefaultImpulse, true);

			}

		}


		//Totam->ApplyDamage(DefaultDamage, Hit.Location, Hit.ImpactPoint, DefaultImpulse);
		//UKismetMathLibrary::
		//TriggerComp->DestroyComponent();
		//TriggerComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		//TriggerComp->SetCollisionResponseToChannel()

	}
}


void ACDestructionCollisionActor::DestroyActor()
{
	TriggerComp->DestroyComponent();
	//UGameplayStatics::PlaySoundAtLocation(this, DestructSound, GetActorLocation());
	//Destroy();
}

void ACDestructionCollisionActor::Summon()
{
}

void ACDestructionCollisionActor::Destruction()
{
	//TriggerComp->DestroyComponent();
	UGameplayStatics::PlaySoundAtLocation(this, DestructSound, GetActorLocation());

	GetWorldTimerManager().SetTimer(CountdownTimerHandle, this, &ACDestructionCollisionActor::DestroyActor, 0.2f, false);
	
}

