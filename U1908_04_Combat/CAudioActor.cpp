// Fill out your copyright notice in the Description page of Project Settings.


#include "CAudioActor.h"
#include "Global.h"
#include "Components/AudioComponent.h"
// Sets default values
ACAudioActor::ACAudioActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AudioComp = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComp"));
	AudioComp->SetupAttachment(RootComponent);

	AudioComp1 = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComp1"));
	AudioComp1->SetupAttachment(RootComponent);

	AudioComp2 = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComp2"));
	AudioComp2->SetupAttachment(RootComponent);




	FString path;
	//Item
	{
		path = L"SoundCue'/Game/Music/03_-_Dusk_Horizon_Cue.03_-_Dusk_Horizon_Cue'";
		ConstructorHelpers::FObjectFinder<USoundBase> music1(*path);
		if (music1.Succeeded())
			Musiclist.Add(music1.Object);

		path = L"SoundCue'/Game/Music/1-21_TAKUMI_1988_Cue.1-21_TAKUMI_1988_Cue'";
		ConstructorHelpers::FObjectFinder<USoundBase> music2(*path);
		if (music2.Succeeded())
			Musiclist.Add(music2.Object);

		path = L"SoundCue'/Game/Music/015_-_Chasing_Daybreak__Thunder__Cue.015_-_Chasing_Daybreak__Thunder__Cue'";
		ConstructorHelpers::FObjectFinder<USoundBase> music3(*path);
		if (music3.Succeeded())
			Musiclist.Add(music3.Object);
	}
}

void ACAudioActor::PlayMusic(uint32 musiclist)
{
	//return;
	//CLog::Print(TEXT("PlayMusic"));
	AudioComp1->SetSound(Musiclist[musiclist]);
	AudioComp1->FadeIn(2, 1, 0);
	AudioComp->FadeOut(1, 0.0f);
}

void ACAudioActor::FadeOut()
{
	//return;
	//CLog::Print(TEXT("FadeOut"));
	AudioComp1->FadeOut(1, 0.0f);
	if (bGetInBossRoom)
		AudioComp2->FadeOut(1, 0.0f);
	//AudioComp->Play();
	AudioComp->FadeIn(2, 1, GetGameTimeSinceCreation());
	//AudioComp->FadeIn(2, 1, 0);
}

// Called when the game starts or when spawned
void ACAudioActor::BeginPlay()
{
	Super::BeginPlay();
	//return;
	AudioComp->SetSound(Musiclist[0]);

	AudioComp1->SetSound(Musiclist[1]);

	AudioComp2->SetSound(Musiclist[2]);
	if(bGetInBossRoom)
		AudioComp2->FadeIn(1, 1, 0);
	else
		AudioComp->FadeIn(1, 1, 0);
}

// Called every frame
void ACAudioActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

