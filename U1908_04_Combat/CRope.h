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
		class UCableComponent* Cable; //���̺� ��ü

	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* CableEnd;//��� �� �κ�

	UPROPERTY(VisibleAnywhere)
		class UPhysicsConstraintComponent* PhysicsConstraint;
		//���̺� ó���κа� ���κ��� �����մϴ�.

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UCapsuleComponent* Capsule;//���̺� �浹ü
	UFUNCTION()
	void IsGrabed(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, 
		bool bFromSweep, const FHitResult & SweepResult);
	//���̺� �浹������ ��� ���°� �˴ϴ�.

	UStaticMeshComponent* GetCableEnd() { return CableEnd; }
	//�÷��̾�� ���κ��� ������ �ݴϴ�.

	class ACCombatCharacter* player;
	
	UFUNCTION()
		void AddSwingforce(FVector force);//����Ű�� �����̴� ������ �����մϴ�

	bool bGarbed;
};
