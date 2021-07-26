// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CFallRespawn.generated.h"

UCLASS()
class U1908_04_COMBAT_API ACFallRespawn : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACFallRespawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;

	UFUNCTION()
		void IsGrabed(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION()
		void Spawn();

	class ACCombatCharacter* Pawn;
private:
	UPROPERTY(EditAnywhere)
		class USphereComponent* TransferVolume;

	UPROPERTY(EditAnywhere)
		class USceneComponent* SpawnTransform;

	
};
