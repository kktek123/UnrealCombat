// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CEnemy.h"
#include "UIRotate.h"
#include "Enums/CEnum0.h"
#include "CEnemy_Sword.generated.h"



UCLASS()
class U1908_04_COMBAT_API ACEnemy_Sword : public ACEnemy
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACEnemy_Sword();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void TakeDamage();
public:	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void OnBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	//					겹치는 컴포넌트							충돌한 엑터				어느컴포넌트와 충돌했는지		본번호					스윕검사		스윕된 결과								
	UFUNCTION()
		void OnEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);



};

