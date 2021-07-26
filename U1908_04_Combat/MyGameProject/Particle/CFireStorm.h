// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CFireStorm.generated.h"

UCLASS()
class U1908_04_COMBAT_API ACFireStorm : public AActor
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleDefaultsOnly)
		class UParticleSystemComponent* FireStorm;

	UPROPERTY(VisibleDefaultsOnly)
		class UBoxComponent* CollisionComp;

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

	int32 CountdownTime;
	FTimerHandle CountdownTimerHandle;

	FVector location;
	FVector forward;
private:
	void AdvanceTimer();
public:	
	// Sets default values for this actor's properties
	ACFireStorm();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
