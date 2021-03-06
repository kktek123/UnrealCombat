// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CEnemy.h"
#include "UIRotate.h"
#include "Enums/CEnum0.h"
#include "CEnemy_Big.generated.h"

/**
 * 
 */
UCLASS()
class U1908_04_COMBAT_API ACEnemy_Big : public ACEnemy
{
	GENERATED_BODY()
public:
	// Sets default values for this character's properties
	ACEnemy_Big();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void TakeDamage();
public:
	virtual void Tick(float DeltaTime) override;
	FTimerHandle CountdownTimerHandle;

	float fString;

	UFUNCTION()
		void OnString();
	UFUNCTION()
		void OnShoot();

	UFUNCTION()
		void OnBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	//					??ġ?? ??????Ʈ							?浹?? ????				??????????Ʈ?? ?浹?ߴ???		????ȣ					?????˻?		?????? ????								
	UFUNCTION()
		void OnEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


};
