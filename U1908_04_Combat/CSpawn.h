// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CSpawn.generated.h"

UCLASS()
class U1908_04_COMBAT_API ACSpawn : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACSpawn();

	void Spawn();
	void Summon();
	bool IsDead();
	void SetLastOne();
	bool bDead;
	class ACEnemy* GetEnemy() { return Enemy; }
	class ACWallBlock* WallBlock;
	class ACDestructionActor* Destruction;
	UPROPERTY(VisibleDefaultsOnly, Category = "Effect")
		class UParticleSystemComponent* SummonEffect;
	//class ACWallBlock* GetWallBlock() { return WallBlock; }
	FTimerHandle SummonTimerHandle;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Enemy")
		TSubclassOf<class ACEnemy> EnemyClass;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UPROPERTY(EditAnywhere, Category = "Wall")
		TSubclassOf<class ACWallBlock> WallBlockClass;

	
private:
	class ACEnemy* Enemy;
	void ShutDownEffect();
	UPROPERTY(EditAnywhere, Category = "bool")
		bool bSummon;
	bool bSetLastOne;
};
