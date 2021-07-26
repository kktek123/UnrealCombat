// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "Components/DecalComponent.h"
#include "GameFramework/Actor.h"
#include "CSpellIndicator.generated.h"

UCLASS()
class U1908_04_COMBAT_API ACSpellIndicator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACSpellIndicator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
		UDecalComponent* Decal;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
