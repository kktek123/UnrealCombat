// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CBoom.generated.h"

UCLASS()
class U1908_04_COMBAT_API ACBoom : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACBoom();

public:
	UPROPERTY(VisibleDefaultsOnly)
		class UStaticMeshComponent* Boom;

	UPROPERTY(VisibleDefaultsOnly)
		class USphereComponent* CollisionComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
		class UProjectileMovementComponent* ProjectileMovement;


	UPROPERTY(EditAnywhere)
		FString AttachName = "ArrowShootLocation";

	UPROPERTY(EditAnywhere)
		FString ShootName = "ArrowShootLocation";

	class UParticleSystem* Particle;

	UPROPERTY(EditAnywhere)
		float Height = 100.0f;
	UPROPERTY(EditAnywhere)
		float Radius = 200.0f;

	UPROPERTY(EditAnywhere)
		float Power = 30.0f;

	UPROPERTY(EditAnywhere)
		float dlPos;

	UPROPERTY(EditAnywhere)
		bool fallen;
	FTimerHandle CountdownTimerHandle;

	bool GetHitType() { return true; }

	UPROPERTY(EditAnywhere)
		class USoundBase* BoomSound;
	///** Returns CollisionComp subobject **/
	//FORCEINLINE class USphereComponent* GetCollisionComp() const { return CollisionComp; }
	///** Returns ProjectileMovement subobject **/
	//FORCEINLINE class UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovement; }

public:

	void Draw();
	void Shoot();
	UFUNCTION()
		void Explosion(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


private:
	bool bShooting;
	bool bDrawing;

	FHitResult HitResult;
	TArray<AActor*> AtI;
	float boomsound;

	class ACharacter* Player;
	class ACCombatCharacter* CombatPlayer;
	class UCameraComponent* PlayerCamera;
	class USceneComponent* PlayerHolding;
	class USceneComponent* PlayerShooting;

	class ACSpellIndicator* SpellIndicator;
	UPROPERTY(EditAnywhere)
		TSubclassOf<class ACSpellIndicator> MagicClass;

};
