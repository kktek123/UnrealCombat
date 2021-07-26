// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CHuricain.generated.h"

UCLASS()
class U1908_04_COMBAT_API ACHuricain : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACHuricain();

	UPROPERTY(VisibleDefaultsOnly)
		class UParticleSystemComponent* Huricain;

	UPROPERTY(VisibleDefaultsOnly)
		class UBoxComponent* CollisionComp;

	class UParticleSystem* Particle;

	UPROPERTY(EditAnywhere)
		float Height = 100.0f;
	UPROPERTY(EditAnywhere)
		float Radius = 200.0f;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
		void OnBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
		void OnEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


};
