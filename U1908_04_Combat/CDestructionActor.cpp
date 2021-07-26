// Fill out your copyright notice in the Description page of Project Settings.


#include "CDestructionActor.h"
#include "Global.h"
#include "CCombatCharacter.h"
#include "CEnemy.h"
#include "Components/SphereComponent.h"
#include "FireWall.h"
#include "CSpawn.h"
#include "CWallBlock.h"
#include "TimeSynthComponent.h"

ACDestructionActor::ACDestructionActor()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComp"));
	//CollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("SphereComp"));
	//CollisionComp->BodyInstance.SetCollisionProfileName("Trigger");
	//CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &ACWallBlock::OnBlock);
	Totam = CreateDefaultSubobject<UDestructibleComponent>(TEXT("Totam"));
	Totam->SetupAttachment(RootComponent);
	Totam->SetNotifyRigidBodyCollision(true);
	
	
	TriggerComp = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerComp"));
	TriggerComp->SetupAttachment(RootComponent);

	IsDestroyed = false;
	IsTiggerEnable = false;

	MaxHealth = 100.0f;
	
	DefaultDamage = 1.0f;
	DefaultImpulse = 1.0f;

	SpectrumBarSpacing = 100.0f;

	TimeSynthComp = CreateDefaultSubobject<UTimeSynthComponent>("TimeSynthComponent");
	TimeSynthComp->bEnableSpectralAnalysis = true;

}

void ACDestructionActor::BeginPlay()
{
	Super::BeginPlay();
	Totam->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	CurrentHealth = MaxHealth;
	Totam->OnComponentHit.AddDynamic(this, &ACDestructionActor::Damage);
}

float ACDestructionActor::TakeDamage(float Damage, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	if (!DamageCauser->IsA(ACCombatCharacter::StaticClass())) return 0;

	CurrentHealth -= Damage;

	
	if (CurrentHealth <= 0)
	{
		if (!IsDestroyed)
		{
			//CLog::Print(TEXT("TakeDamage"));
			IsDestroyed = true;
			//Totam->ApplyDamage(10000, Totam->GetComponentLocation(), Totam->GetForwardVector(), 100);
			Totam->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
			Totam->SetCollisionObjectType(ECollisionChannel::ECC_Destructible);

			Totam->ApplyRadiusDamage(Damage, GetActorLocation(),1,1,true);
			GetWorldTimerManager().SetTimer(CountdownTimerHandle, this, &ACDestructionActor::Destroy, 0.5f, false);

			Summon();
		}
	}

	return Damage;
}

// Called every frame
void ACDestructionActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACDestructionActor::Summon()
{
	Trigger();
	//if (SpawnClass != NULL)//	if (SummonClass != NULL)
	//{
		//UWorld* const World = GetWorld();
		//if (World != NULL)
		//{
		//	const FRotator SpawnRotation = GetActorRotation();
		//	//GetControlRotation();
		////FVector SpawnLocation = UKismetMathLibrary::RandomPointInBoundingBox(GetActorLocation(), FVector(500, 500, 0));// +FVector(100.0f, 0.0f, 10.0f);
		////((ArrowLocation != nullptr) ? 
		////ArrowLocation->GetComponentLocation() : GetActorLocation()) + SpawnRotation.RotateVector({ 100.0f, 0.0f, 10.0f });

		//	FActorSpawnParameters ActorSpawnParams;
		//	//ActorSpawnParams.Owner = this;
		//	ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
		//	//if (IsValid(ArrowClass))
		//	for (int i = 0; i < SummonCount; i++)
		//	{
		//		FVector SpawnLocation = UKismetMathLibrary::RandomPointInBoundingBox(GetActorLocation(), FVector(1000, 1000, 0));// +FVector(100.0f, 0.0f, 10.0f);
		//		//World->SpawnActor<ACEnemy>(SummonClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
		//		World->SpawnActor<ACSpawn>(SpawnClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
		//	}
		//}
		//if (bGenerate) return;
		//for (int i = 0; i < Wall.Num(); i++)
		//{
		//	Wall[i]->OnBlock();
		//}
		//for (int i = 0; i < Spawner.Num(); i++)
		//{
		//	Spawner[i]->Spawn();
		//	Spawner[i]->Destruction = this;
		//	if (Spawner.Num() == 1)
		//	{
		//		if (IsValid(Spawner[0]))
		//		{
		//			Spawner[0]->SetLastOne();
		//			CLog::Print(TEXT("bSetLastOne"));
		//		}
		//	}
		//}
		//bGenerate = true;

	//}

}

void ACDestructionActor::Damage(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor->IsA(ACCombatCharacter::StaticClass()))
	{
		
		CurrentHealth -= 1;

		Totam->ApplyDamage(DefaultDamage, Hit.Location, NormalImpulse, DefaultImpulse);
		if (CurrentHealth <= 0)
		{
			//Totam->ApplyDamage(DefaultDamage, Location, ImpulseDir, DefaultImpulse);

			//Destroy();
			if (!IsDestroyed)
			{
				//CLog::Print(TEXT("Destroyed"));
				IsDestroyed = true;
				Summon();
			}
			
		}
	}

}

void ACDestructionActor::Trigger()
{
	trigger->OnTrigger();
}

void ACDestructionActor::Destroy()
{
	//UGameplayStatics::PlaySoundAtLocation(this, PainSound, GetActorLocation());
	//if (!IsDestroyed)
	//	IsDestroyed = true;
	TriggerComp->DestroyComponent();
}

void ACDestructionActor::PostEditChangeProperty(FPropertyChangedEvent & PropertyChangedEvent)
{
}

void ACDestructionActor::Refresh()
{
}

