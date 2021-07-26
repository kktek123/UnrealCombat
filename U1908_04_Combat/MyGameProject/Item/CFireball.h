// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CFireball.generated.h"

UCLASS()
class U1908_04_COMBAT_API ACFireball : public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleDefaultsOnly)
		class UParticleSystemComponent* Fireball;

	UPROPERTY(VisibleDefaultsOnly)
		class USphereComponent* CollisionComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
		class UProjectileMovementComponent* ProjectileMovement;


	UPROPERTY(EditAnywhere)
		FString AttachName = "FireballLocation";

	UPROPERTY(EditAnywhere)
		FString ShootName = "ShootRightLocation";

	class UParticleSystem* Particle;

	UPROPERTY(EditAnywhere)
		float Height = 100.0f;
	UPROPERTY(EditAnywhere)
		float Radius = 200.0f;
public:	
	// Sets default values for this actor's properties
	ACFireball();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Charge();
	void Shoot();

	UPROPERTY(EditAnywhere)
		class USoundBase* BoomSound;

	UFUNCTION()
		void Explosion(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

private:
	bool bShooting;
	bool bChargeing;

	class ACharacter* Player;
	class ACCombatCharacter* CombatPlayer;
	class UCameraComponent* PlayerCamera;
	class USceneComponent* PlayerHolding;
	class USceneComponent* PlayerShooting;


};
