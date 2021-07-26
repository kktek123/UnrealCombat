// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CWindBlade.generated.h"

UCLASS()
class U1908_04_COMBAT_API ACWindBlade : public AActor
{
	GENERATED_BODY()
	

public:
	UPROPERTY(VisibleDefaultsOnly)
		class UParticleSystemComponent* WindBlade;

	UPROPERTY(VisibleDefaultsOnly)
		class UCapsuleComponent* CollisionComp;

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
	ACWindBlade();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
