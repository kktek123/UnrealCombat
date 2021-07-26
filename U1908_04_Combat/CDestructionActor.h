// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DestructibleComponent.h"
#include "CDestructionActor.generated.h"

UCLASS()
class U1908_04_COMBAT_API ACDestructionActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACDestructionActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		TArray<class AFireWall*>Wall;

	UPROPERTY(EditAnywhere)
		TArray<class ACSpawn*>Spawner;

	UPROPERTY(EditAnywhere, Category = "Class")
		class ACWallBlock* trigger;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Destructible")
		class UBoxComponent* TriggerComp;

	//UFUNCTION()
	//	void OnBlock(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	//UFUNCTION()
	//	void OffBlock();


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Destructible")
		class UDestructibleComponent* Totam;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Destructible")
		bool IsDestroyed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Destructible")
		bool IsTiggerEnable;


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Destructible")
		float MaxHealth;


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Destructible")
		float CurrentHealth;


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Destructible")
		float DefaultDamage;


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Destructible")
		float DefaultImpulse;

	UPROPERTY(EditAnywhere, Category = "Summon")
		TSubclassOf<class ACSpawn> SpawnClass;

	UPROPERTY(EditAnywhere, Category = "Summon")
		float SummonCount = 10;
	void Summon();
	void Damage(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	void Trigger();
	void Destroy();

protected:
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)override;

	void Refresh();

	UPROPERTY(EditDefaultsOnly, Category = "Class")
		TArray<TSubclassOf<class AFireWall>> wallClasses;

	UPROPERTY(EditDefaultsOnly, Category = "Class")
		TArray<TSubclassOf<class ACSpawn>> spawnClasses;

	FTimerHandle CountdownTimerHandle;

	bool bGenerate;

	UPROPERTY(EditAnywhere, Category = "Audio")
		class UTimeSynthComponent* TimeSynthComp;

	UPROPERTY(EditAnywhere, Category = "Audio")
		class UTimeSynthClip* TimeSynthClip;

	UPROPERTY(EditAnywhere, Category = "Audio")
		TArray<UStaticMeshComponent*> SpectrumBars;

	UPROPERTY(EditAnywhere, Category = "Audio")
		UStaticMesh* SpectrumBarMesh;

	UPROPERTY(EditAnywhere, Category = "Audio")
		float SpectrumBarSpacing;

};
