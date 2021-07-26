// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CEnemy.h"
#include "CEnemy_Fly.generated.h"

/**
 * 
 */
UCLASS()
class U1908_04_COMBAT_API ACEnemy_Fly : public ACEnemy
{
	GENERATED_BODY()
public:
	ACEnemy_Fly();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void TakeDamage();
public:
	virtual void Tick(float DeltaTime) override;
	FTimerHandle CountdownTimerHandle;

	UFUNCTION()
		void OnBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	//					��ġ�� ������Ʈ							�浹�� ����				���������Ʈ�� �浹�ߴ���		����ȣ					�����˻�		������ ���								
	UFUNCTION()
		void OnEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:

	UFUNCTION()
		void Progress(float Value);

	UFUNCTION()
		void ResetProgress();

	void UpdateFlightTimeline(UCurveFloat* CurveFloat);

};
