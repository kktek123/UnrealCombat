// Fill out your copyright notice in the Description page of Project Settings.


#include "DeadCineCameraActor.h"

ADeadCineCameraActor::ADeadCineCameraActor(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
}

void ADeadCineCameraActor::BeginPlay()
{
}

void ADeadCineCameraActor::Tick(float DeltaTime)
{
}

bool ADeadCineCameraActor::ShouldTickIfViewportsOnly() const
{
	return false;
}

void ADeadCineCameraActor::PostInitializeComponents()
{
}


