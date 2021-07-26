// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DestructibleComponent.h"
#include "CDestructionCollisionActor.generated.h"

UCLASS()
class U1908_04_COMBAT_API ACDestructionCollisionActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACDestructionCollisionActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);



	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Destructible")
		class UBoxComponent* TriggerComp;

	FTimerHandle CountdownTimerHandle;

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

	void DestroyActor();
	void Summon();
	void Destruction();
	bool bDestruction;

	class ACEnemy* colpawn;

	UPROPERTY(EditAnywhere)
		class USoundBase* DestructSound;
};
