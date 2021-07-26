// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBase.h"
#include "CWallBlock.generated.h"

/**
 * 
 */
UCLASS()
class U1908_04_COMBAT_API ACWallBlock : public ATriggerBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleDefaultsOnly)
		class UBoxComponent* CollisionComp;

	UPROPERTY(EditAnywhere)
		class UAudioComponent* AudioComp;

	UFUNCTION()
		void OnBlock(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
		void OffBlock();

	UFUNCTION()
		void Wave2();

	UFUNCTION()
		void Wave3();

	UFUNCTION()
		void OnTrigger();
public:
	// Sets default values for this actor's properties
	ACWallBlock();

	UPROPERTY(EditAnywhere)
		TArray<class AFireWall*>Wall;

	//UPROPERTY(EditAnywhere)
	//	TArray<class ACSpawn*>Spawner;

	UPROPERTY(EditAnywhere, Category = "Wave1")
		TArray<class ACSpawn*>Spawner;

	UPROPERTY(EditAnywhere, Category = "Wave2")
		TArray<class ACSpawn*>Spawner2;

	UPROPERTY(EditAnywhere, Category = "Wave3")
		TArray<class ACSpawn*>Spawner3;

	//UPROPERTY(EditAnywhere)
	//	TArray<class ACAmbientSound*>Sound;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		USoundBase* MusicSound;

	UPROPERTY(EditAnywhere, Category = "audio")
		class ACAudioActor* audio;

	UPROPERTY(EditDefaultsOnly, Category = "audio")
		TSubclassOf<class ACAudioActor> audioClass;


protected:
	UPROPERTY(EditDefaultsOnly, Category = "Class")
		TArray<TSubclassOf<class AFireWall>> wallClasses;

	UPROPERTY(EditDefaultsOnly, Category = "Class")
		TArray<TSubclassOf<class ACSpawn>> spawnClasses;

	UPROPERTY(EditAnywhere)
		bool bWave1;

	UPROPERTY(EditAnywhere)
		bool bWave2;
	UPROPERTY(EditAnywhere)
		bool bWave3;

	bool bGenerate;


};
