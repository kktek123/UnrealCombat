#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GenericTeamAgentInterface.h"
#include "CPlayer.generated.h"

UCLASS()
class U1908_04_COMBAT_API ACPlayer : public ACharacter, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

public:
	ACPlayer();

private:
	UPROPERTY(EditDefaultsOnly, Category = "Camera")
		float ZoomSpeed = 20.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Movement")
		float WalkSpeed = 400.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Movement")
		float RunSpeed = 600.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
		TSubclassOf<class ACSword> SwordClass;
	
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
		class UAnimMontage* AttackMontage;

protected:
	virtual void BeginPlay() override;

public:
	FGenericTeamId GetGenericTeamId() const override 
	{
		return FGenericTeamId(2);
	};

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	bool GetDrawing() { return bDrawing; }
	bool GetSheathing() { return bSheathing; }
	class ACSword* GetSword() { return Sword; }


private:
	void OnMoveForward(float Value);
	void OnMoveRight(float Value);
	void OnTurn(float Value);
	void OnLookUp(float Value);
	void OnZoom(float Value);

	void OnRunning();
	void OffRunning();

	void OnJumping();

	void OnEquip();
	void OnAttacking();

private:
	void Equip();
	void Sheath();

public:
	void Equipped();
	void Sheathed();

	void BeginAttack();
	void EndAttack();

private:
	class USpringArmComponent* SpringArm;
	class ACSword* Sword;
	
	bool bCanMove = true;
	bool bAttacking = false;

	bool bFoward;
	bool bDrawing;
	bool bSheathing;

	bool bDrawn;
};
