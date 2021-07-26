// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CLevelChange.generated.h"

UCLASS()
class U1908_04_COMBAT_API ACLevelChange : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACLevelChange();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
		FName LevelName;

	UPROPERTY()
		class UBoxComponent* TransferVolume;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
