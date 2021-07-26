// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enums/CEnum0.h"
#include "CDisplayedItem.generated.h"

UCLASS()
class U1908_04_COMBAT_API ACDisplayedItem : public AActor
{
	GENERATED_BODY()
	

public:
	ACDisplayedItem();
	ACDisplayedItem(const class FObjectInitializer& Object);

public:

	void SetOwningPawn(class ACParty* NewOwner);
	void AttachMeshToPawn();
	void OnEquip(const ACDisplayedItem* LastWeapomn);
	void OnUnEquip();
	E_WeaponType GetWeaponType() { return weaponType; }

	UFUNCTION()
		void ChangeSpell();

	UFUNCTION()
		void CastSpell();

	UFUNCTION()
		void UnCastSpell();

	UFUNCTION()
		void Gen_Particle();


	void SetAimAlpha(float f);
	
protected:
	UPROPERTY(VisibleAnywhere)
		class UCapsuleComponent* Capsule;

	UPROPERTY(VisibleAnywhere)
		USkeletalMeshComponent* SkMesh;

	UPROPERTY(VisibleAnywhere, Category = "Weapon")
		UStaticMeshComponent* WeaponMesh;

	
	UPROPERTY(VisibleAnywhere)
		USphereComponent* Magic;

	class ACCombatCharacter* MyPawn;



	UPROPERTY(EditAnywhere)
		float Power = 10.0f;

	UPROPERTY(EditAnywhere)
		float Height = 100.0f;
	UPROPERTY(EditAnywhere)
		float Radius = 200.0f;

	UPROPERTY(EditAnywhere)
		float AimAlpha;

	E_WeaponType weaponType;

	UPROPERTY(VisibleDefaultsOnly)
		class UParticleSystemComponent* Fireball;

	UPROPERTY(VisibleDefaultsOnly)
		class UParticleSystemComponent* Heal;

	UPROPERTY(VisibleDefaultsOnly)
		class UParticleSystemComponent* Storm;

	UPROPERTY(VisibleDefaultsOnly)
		class UParticleSystemComponent* Boom;

	UPROPERTY(VisibleDefaultsOnly)
		class UParticleSystemComponent* Burf;

private:

	UPROPERTY(EditDefaultsOnly)
		FName AttachmentSocket;

	UPROPERTY(VisibleAnywhere)
		class UStaticMeshComponent* StaticMesh;

public:
	UFUNCTION(BlueprintPure)
		class UCapsuleComponent* GetCapsule() { return Capsule; }
	UFUNCTION(BlueprintPure)
		USkeletalMeshComponent* GetSkMesh() { return SkMesh; }
	UFUNCTION(BlueprintPure)
		UStaticMeshComponent* GetMesh() { return StaticMesh; }
	UFUNCTION(BlueprintPure)
		USphereComponent* GetParticle() { return Magic; }
	UFUNCTION(BlueprintPure)
		UStaticMeshComponent* GetWeaponMesh() { return WeaponMesh; }

	UPROPERTY(EditAnywhere)
		class USoundBase* BoomSound;


public:
	//UFUNCTION(BlueprintPure)
	//	UPrimitiveComponent* GetPrimaryComponent();

	//UFUNCTION()
	//	bool Attach();

	//UFUNCTION(BlueprintPure)
	//	virtual FName GetAttachmentSocket();

	//UFUNCTION()
	//	void SimulatePhysics();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditAnywhere)
		class UParticleSystem* Particle;
};
