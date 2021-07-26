// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CRope.generated.h"

UCLASS()
class U1908_04_COMBAT_API ACRope : public AActor
{
	GENERATED_BODY()
	
public:	
	ACRope();

protected:
	virtual void BeginPlay() override;


	UPROPERTY(VisibleAnywhere)
		class UCableComponent* Cable; //케이블 본체

	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* CableEnd;//잡는 끝 부분

	UPROPERTY(VisibleAnywhere)
		class UPhysicsConstraintComponent* PhysicsConstraint;
		//케이블 처음부분과 끝부분을 연결합니다.

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UCapsuleComponent* Capsule;//케이블 충돌체
	UFUNCTION()
	void IsGrabed(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, 
		bool bFromSweep, const FHitResult & SweepResult);
	//케이블에 충돌했을때 잡는 상태가 됩니다.

	UStaticMeshComponent* GetCableEnd() { return CableEnd; }
	//플래이어에게 끝부분의 정보를 줍니다.

	class ACCombatCharacter* player;
	
	UFUNCTION()
		void AddSwingforce(FVector force);//방향키로 움직이는 방향을 조절합니다

	bool bGarbed;
};
