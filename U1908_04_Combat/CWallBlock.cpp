// Fill out your copyright notice in the Description page of Project Settings.


#include "CWallBlock.h"
#include "Global.h"
#include "CCombatCharacter.h"
#include "CEnemy.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"
#include "FireWall.h"
#include "CSpawn.h"
#include "CAudioActor.h"
#include "Components/AudioComponent.h"

ACWallBlock::ACWallBlock()
{
	CollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("SphereComp"));
	CollisionComp->BodyInstance.SetCollisionProfileName("Trigger");
	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &ACWallBlock::OnBlock);		// set up a notification for when this component hits something blocking

	AudioComp = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComp"));
	// Players can't walk on it
	RootComponent = CollisionComp;


	FString path;


	path = L"Blueprint'/Game/MyCAudioActor.MyCAudioActor_C'";
	ConstructorHelpers::FClassFinder<ACAudioActor> music(*path);
	if (music.Succeeded())
		audioClass = music.Class;
}

void ACWallBlock::BeginPlay()
{
	FTransform transform = FTransform::Identity;
	FActorSpawnParameters params;
	params.Owner = this;
	//RetNull(audioClass);
	//audio = GetWorld()->SpawnActor<ACAudioActor>(audioClass, transform, params);

	RetNull(MusicSound);
	AudioComp->SetSound(MusicSound);
}

void ACWallBlock::Tick(float DeltaTime)
{

	
}
void ACWallBlock::OnBlock(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor->IsA(ACParty::StaticClass()))
	{
		OnTrigger();
	}
	//Destroy();
}

void ACWallBlock::OffBlock()
{
	float answer = 0;
	TArray<ACSpawn*>thisSpawner;
	if (bWave1)
		thisSpawner = Spawner;
	else if (!bWave1 && bWave2)
		thisSpawner = Spawner2;
	else if (!bWave2 && bWave3)
		thisSpawner = Spawner3;

	for (int i = 0; i < thisSpawner.Num(); i++)
	{
		//if (IsValid(Spawner[i]))
		
			if (thisSpawner[i]->bDead == true)
				answer++;
	}
	if (answer >= thisSpawner.Num() - 1)
	{
		for (int i = 0; i < thisSpawner.Num(); i++)
		{
			if (IsValid(thisSpawner[i]))
				thisSpawner[i]->GetEnemy()->bLastOne = true;
		}
	}
	if (answer >= thisSpawner.Num())
	{
		if (!bWave1 && !bWave2)
			bWave3 = false;
		if (!bWave1)
			bWave2 = false;

		if (bWave2)
		{
			bWave1 = false;
			Wave2();
		}
		else if (bWave3)
		{
			bWave2 = false;
			Wave3();
		}
		else
		{
			for (int i = 0; i < Wall.Num(); i++)
			{
				Wall[i]->OffBlock();
			}
			answer = 0;
			RetNull(audio);
			audio->FadeOut();
		}

		//audio->PlayMusic(0);
		//RetNull(MusicSound);
		//AudioComp->FadeOut(2,0.0f);
	}
	
	//UGameplayStatics::de(this, TEXT("MusicSound"));

}

void ACWallBlock::Wave2()
{
	//if (bWave2)return;
	//bWave2 = true;
	for (int i = 0; i < Spawner2.Num(); i++)
	{
		Spawner2[i]->Spawn();
		Spawner2[i]->WallBlock = this;
		if (Spawner2.Num() == 1)
		{
			if (IsValid(Spawner2[0]))
			{
				Spawner2[0]->SetLastOne();
				CLog::Print(TEXT("bSetLastOne"));
			}
		}

		//  Sound->AudioComponent();
	}

	
}

void ACWallBlock::Wave3()
{
	//if (bWave3)return;
	//bWave3 = true;
	for (int i = 0; i < Spawner3.Num(); i++)
	{
		Spawner3[i]->Spawn();
		Spawner3[i]->WallBlock = this;
		if (Spawner3.Num() == 1)
		{
			if (IsValid(Spawner3[0]))
			{
				Spawner3[0]->SetLastOne();
				CLog::Print(TEXT("bSetLastOne"));
			}
		}

		//  Sound->AudioComponent();
	}
}

void ACWallBlock::OnTrigger()
{
	if (bGenerate) return;
	for (int i = 0; i < Wall.Num(); i++)
	{
		Wall[i]->OnBlock();
	}
	for (int i = 0; i < Spawner.Num(); i++)
	{
		Spawner[i]->Spawn();
		Spawner[i]->WallBlock = this;
		if (Spawner.Num() == 1)
		{
			if (IsValid(Spawner[0]))
			{
				Spawner[0]->SetLastOne();
				CLog::Print(TEXT("bSetLastOne"));
			}
		}
		
		//  Sound->AudioComponent();
	}
	bGenerate = true;
	RetNull(audio);
	audio->PlayMusic(1);
	RetNull(MusicSound);
	//UGameplayStatics::PlaySound2D(this, MusicSound);
	//AudioComp->Play();
	//AudioComp->FadeIn(2,1,0);

}
