// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CArrow.generated.h"

UCLASS()
class U1908_04_COMBAT_API ACArrow : public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleDefaultsOnly)
		class UStaticMeshComponent* Arrow;

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

	///** Returns CollisionComp subobject **/
	//FORCEINLINE class USphereComponent* GetCollisionComp() const { return CollisionComp; }
	///** Returns ProjectileMovement subobject **/
	//FORCEINLINE class UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovement; }

public:	
	// Sets default values for this actor's properties
	ACArrow();

	void Draw();
	void Shoot();
	UFUNCTION()
		void Explosion(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	UFUNCTION()
		void SpawnImpactedArrow(USceneComponent* Component,FName SocketName,AActor* actor,FVector Vector);

	void OnShoot(FVector target);
	//void On
	void DestroyArrow();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "ImpactedArrow")
		TSubclassOf<class ACImpactedArrow> ImpactedArrowClass;


	bool bShooting;
private:
	bool bHit;
	bool bDrawing;
	FHitResult HitResult;
	TArray<AActor*> AtI;
	FTimerHandle Destroytime;
	class ACharacter* Player;
	class ACCombatCharacter* CombatPlayer;
	class UCameraComponent* PlayerCamera;
	class USceneComponent* PlayerHolding;
	class USceneComponent* PlayerShooting;
	class ACImpactedArrow* ImpactedArrow;
};
