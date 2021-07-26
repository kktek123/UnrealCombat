// Fill out your copyright notice in the Description page of Project Settings.


#include "CSpawn.h"
#include "Global.h"
#include "CEnemy.h"
#include "CCStateManager.h"
#include "CWallBlock.h"
#include "CDestructionActor.h"
// Sets default values
ACSpawn::ACSpawn()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SummonEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("SummonEffect"));
	SummonEffect->SetupAttachment(RootComponent);
	SummonEffect->SetHiddenInGame(true);

}

// Called when the game starts or when spawned
void ACSpawn::BeginPlay()
{
	Super::BeginPlay();
	if (bSummon)
		Spawn();
}

// Called every frame
void ACSpawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//RetNull(Enemy);
	//if(!bDead)
	//	IsDead();
}

void ACSpawn::ShutDownEffect()
{
	FTransform transform = FTransform::Identity;
	FActorSpawnParameters params;
	params.Owner = this;
	RetNull(EnemyClass);
	Enemy = GetWorld()->SpawnActor<ACEnemy>(EnemyClass, GetActorLocation(), GetActorRotation(), params);
	Enemy->SetMySummon(this);
	if (bSetLastOne == true)
	{
		GetEnemy()->bLastOne = true;
		CLog::Print(TEXT("SetLastOne"));
	}
	SummonEffect->SetHiddenInGame(true);
}



void ACSpawn::Spawn()
{
	//CLog::Print(TEXT("Spawn"));
	//FTransform transform = FTransform::Identity;
	//FActorSpawnParameters params;
	//params.Owner = this;
	//RetNull(EnemyClass);
	//Enemy = GetWorld()->SpawnActor<ACEnemy>(EnemyClass, GetActorLocation(), GetActorRotation(), params);

	SummonEffect->SetHiddenInGame(false);
	GetWorldTimerManager().SetTimer(SummonTimerHandle, this, &ACSpawn::ShutDownEffect, 1.0f, false);
}

void ACSpawn::Summon()
{
	//CLog::Print(TEXT("Spawn"));
	FTransform transform = FTransform::Identity;
	FActorSpawnParameters params;
	params.Owner = this;
	RetNull(EnemyClass);

	Enemy = GetWorld()->SpawnActor<ACEnemy>(EnemyClass, GetActorLocation(), GetActorRotation(), params);
	Enemy->SetMySummon(this);
	SummonEffect->SetHiddenInGame(false);
	GetWorldTimerManager().SetTimer(SummonTimerHandle, this, &ACSpawn::ShutDownEffect, 1.0f, false);

}

bool ACSpawn::IsDead()
{
	if (bSummon) return false;
	if (Enemy->GetStateManager()->GetState() == E_State::Dead)
	{
		bDead = true;
		//if(!bDead)
		WallBlock->OffBlock();
		return true;
	}
	return false;
}

void ACSpawn::SetLastOne()
{
	bSetLastOne = true;
}

