// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyGameProject/Item/CDisplayedItem.h"
#include "CDI_Hand.generated.h"

/**
 * 
 */
UCLASS()
class U1908_04_COMBAT_API ACDI_Hand : public ACDisplayedItem
{
	GENERATED_BODY()
	
public:
	ACDI_Hand(const class FObjectInitializer& Object);
	//FName GetAttachmentSocket() override;
	bool gen;
private:

	//UPROPERTY(VisibleAnywhere)
	//	class UStaticMeshComponent* Mesh;

	//UPROPERTY(VisibleAnywhere)
	//	class UCapsuleComponent* Capsule;
private:

	UFUNCTION()
		void OnBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
		void OnEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
		void OnHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	FName HandAttachmentSocket;
	FCollisionShape sphere;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	

};
