// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Enums/CEnum0.h"
#include "MyGameProject/CParty.h"
#include "MyGameProject/PlayerWidget.h"
#include "Components/TimelineComponent.h"
#include "GenericTeamAgentInterface.h"
#include "CCombatCharacter.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnEndAttackDelegate)
DECLARE_MULTICAST_DELEGATE(FOnEndBlockDelegate)
DECLARE_MULTICAST_DELEGATE(FOnAttackHitCheckDelegate)

UCLASS()
class U1908_04_COMBAT_API ACCombatCharacter : public ACParty,public IGenericTeamAgentInterface
{
	GENERATED_BODY()

public:
	ACCombatCharacter();

	USkeletalMeshComponent* GetSpecificPawnMesh() const;

	const FName GetSwordAttachPoint() { return SwordAttachPoint; }
	const FName GetBowAttachPoint() { return BowAttachPoint; }
	const FName GetShieldAttachPoint() { return ShieldAttachPoint; }
	const FName GetSpellAttachPoint() { return SpellAttachPoint; }

	void EquipItem(class ACDisplayedItem* Item);
	void OnChangeItem(int num);
	void WeaponChangeUp();
	void WeaponChangeDown();

	FOnEndBlockDelegate OnEndBlock;
	FOnEndAttackDelegate OnEndAttack;
	FOnAttackHitCheckDelegate OnAttackHitCheck;

	AActor* AttachCamera;

	FTimerHandle CountdownTimerHandle;
	FTimerHandle DamageTimerHandle;
	FTimerHandle DashTimerHandle;

	void enddash();
	UFUNCTION()
		void Setfallpoint();
	void FallingReSpawn();
	FTransform fallpoint;
	bool bcheckfalling;
	UPROPERTY(EditAnywhere)
		TSubclassOf<UCameraShake> MyShake;
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
		FName SwordAttachPoint;
	UPROPERTY(EditDefaultsOnly)
		FName BowAttachPoint;
	UPROPERTY(EditDefaultsOnly)
		FName ShieldAttachPoint;
	UPROPERTY(EditDefaultsOnly)
		FName SpellAttachPoint;

	TArray<class ACDisplayedItem*> Item;

	//TArray<class ACDisplayedItem*> Swords;

	TArray<class ACDisplayedItem*> Shields;

	//TArray<class ACDisplayedItem*> Bows;

	//TArray<class ACDisplayedItem*> Spells;

	class ACDisplayedItem* CurrentItem;
	class ACDisplayedItem* Shield;
	class ACArrow* Arrow;
	class ACFireball* Fireball;
	class ACHuricain* Huricain;

	void AddWeapon(ACDisplayedItem* Item);

	void SetCurrentWeapon(class ACDisplayedItem* NewItem, class ACDisplayedItem* LastItem);


	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
		TSubclassOf<class ACDisplayedItem> ItemClass;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
		TSubclassOf<class ACDisplayedItem> ShieldClass;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
		TArray<TSubclassOf<class ACDisplayedItem>> ItemClasses;

	//UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	//	TArray<TSubclassOf<class ACDisplayedItem>> ShieldClasses;

	//UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	//	TArray<TSubclassOf<class ACDisplayedItem>> SwordClasses;

	//UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	//	TArray<TSubclassOf<class ACDisplayedItem>> BowClasses;

	//UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	//	TArray<TSubclassOf<class ACDisplayedItem>> SpellClasses;

	UPROPERTY(EditAnywhere, Category = "Arrow")
		TSubclassOf<class ACArrow> ArrowClass;

	UPROPERTY(EditAnywhere, Category = "Spell")
		TSubclassOf<class ACFireball> FireballClass;

	UPROPERTY(EditAnywhere, Category = "Huricain")
		TSubclassOf<class ACHuricain> HuricainClass;
	//UPROPERTY(EditAnywhere, Category = "Particle")
	//	TSubclassOf<class ACWindBlade> WindBladeClass;

	//UPROPERTY(EditAnywhere, Category = "Particle")
	//	TSubclassOf<class ACFireStorm> FireStormClass;

	UPROPERTY(EditAnywhere, Category = "Widget")
		TSubclassOf<class UUserWidget> PlayerWidgetClass;

	void SpawnDefaultInventory();

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION()//delegat콜 할때 붙여 준다.
		void OnCapsuleBeginOverlap
		(
			class UPrimitiveComponent* OverlapComp,
			AActor* OtherActor,
			class UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult& SweepResult
		);
	UFUNCTION()//delegat콜
		void OnCapsuleEndOverlap
		(
			class UPrimitiveComponent* OverlapComp,
			AActor* OtherActor,
			class UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex
		);

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	FGenericTeamId GetGenericTeamId() const override
	{
		return FGenericTeamId(2);
	};

	UPROPERTY(VisibleAnywhere)
		class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere)
		class USpringArmComponent* CameraBoomSide;
private:

	UPROPERTY(VisibleAnywhere)
		class UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere)
		class UUserWidget* Widget;
	
	UPROPERTY(VisibleAnywhere)
		class UPlayerWidget* PlayerWidget;

	UPROPERTY(VisibleAnywhere)
		class UStaticMeshComponent* StaticMesh;

	UPROPERTY(VisibleAnywhere)
		class USceneComponent* ArrowLocation;

	UPROPERTY(VisibleAnywhere)
		class USceneComponent* ArrowShootLocation;

	UPROPERTY(VisibleAnywhere)
		class USceneComponent* FireballLocation;

	UPROPERTY(VisibleAnywhere)
		class USceneComponent* ShootRightLocation;

	UPROPERTY(VisibleAnywhere)
		class USceneComponent* ShootLeftLocation;

	UPROPERTY(VisibleAnywhere)
		class USceneComponent* WindBladeLocation;

	UPROPERTY(EditAnywhere)
		class USoundBase* PainSound;

	UPROPERTY(EditAnywhere)
		class USoundBase* ParrySound;

	UPROPERTY(EditAnywhere)
		class USoundBase* BlockSound;

	UPROPERTY(EditAnywhere)
		class USoundBase* SwingSound;

	UPROPERTY(EditAnywhere)
		class USoundBase* SwingHeavySound;

	UPROPERTY(EditAnywhere)
		class USoundBase* SunderSound;

	UPROPERTY(EditAnywhere)
		class USoundBase* DrawSound;

	UPROPERTY(EditAnywhere)
		class USoundBase* SheathSound;

	UPROPERTY(EditAnywhere)
		class USoundBase* ShootArrowSound;

	UPROPERTY(VisibleAnywhere)
		class UCCStateManager* StateManager;

	class ACameraChangeTrigger* ChangeCamera;
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UCExtendedStamina* ExtendedStamina;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UCExtendedStamina* ExtendedHealth;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UTargetComponent* DynamicTargeting;

	UArrowComponent* TargetingArrow;
public:
	class UCCStateManager* GetStateManager() { return StateManager; }

	class UCExtendedStamina* GetExtendedStamina() { return ExtendedStamina; }

	class UCExtendedStamina* GetExtendedHealth() { return ExtendedHealth; }

public:
	void OnSwing();

	USoundBase* GetSwingSound() { return SwingSound; }
	USoundBase* GetSwingHeavySound() { return SwingHeavySound; }
	USoundBase* GetSunderSound() { return SunderSound; }

private:
	UFUNCTION()
		void Progress(float Value);

	UFUNCTION()
		void ResetProgress();

	void UpdateFlightTimeline(UCurveFloat* CurveFloat);
	//UFUNCTION(BlueprintPure)
	//	void CalculateLeanAmount();
private:
	UPROPERTY(EditDefaultsOnly, Category = "Camera")
		float ZoomSpeed = 20.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Movement")
		float BlockSpeed = 200.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Movement")
		float WalkSpeed = 500.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Movement")
		float RunSpeed = 900.0f;

	//UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	//	TSubclassOf<class ACGreateSword> SwordClass;
	//TSubclassOf<class ACGreateSword> SwordClass;

	UPROPERTY(EditDefaultsOnly, Category = "Attack")
		class UAnimMontage* AttackMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Attack")
		class UAnimMontage* AttackComboMontage1;

	UPROPERTY(EditDefaultsOnly, Category = "Attack")
		class UAnimMontage* AttackComboMontage2;

	UPROPERTY(EditDefaultsOnly, Category = "Attack")
		class UAnimMontage* AttackComboMontage3;

	UPROPERTY(EditDefaultsOnly, Category = "Attack")
		class UAnimMontage* AttackComboMontage4;

	UPROPERTY(EditDefaultsOnly, Category = "Attack")
		class UAnimMontage* AttackComboMontage5;


	UPROPERTY(EditDefaultsOnly, Category = "Charge")
		class UAnimMontage* AttackChargeMontage1_1;

	UPROPERTY(EditDefaultsOnly, Category = "Charge")
		class UAnimMontage* AttackChargeMontage2_1;

	UPROPERTY(EditDefaultsOnly, Category = "Charge")
		class UAnimMontage* AttackChargeMontage3_1;

	UPROPERTY(EditDefaultsOnly, Category = "Charge")
		class UAnimMontage* AttackChargeMontage4_1;

	UPROPERTY(EditDefaultsOnly, Category = "Charge")
		class UAnimMontage* AttackChargeMontage5_1;


	UPROPERTY(EditDefaultsOnly, Category = "Parry")
		class UAnimMontage* ParryAttackMontage1;

	UPROPERTY(EditDefaultsOnly, Category = "Parry")
		class UAnimMontage* ParryAttackMontage2;


	UPROPERTY(EditDefaultsOnly, Category = "Block")
		class UAnimMontage* HS_BlockMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Block")
		class UAnimMontage* HS_BlockoffMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Block")
		class UAnimMontage* H_BlockMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Block")
		class UAnimMontage* MS_BlockMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Block")
		class UAnimMontage* M_BlockMontage;

	UPROPERTY(EditDefaultsOnly, Category = "E_S")
		class UAnimMontage* EquipSwordMontage;

	UPROPERTY(EditDefaultsOnly, Category = "E_S")
		class UAnimMontage* SheathSwordMontage;

	UPROPERTY(EditDefaultsOnly, Category = "E_S")
		class UAnimMontage* EquipBowMontage;

	UPROPERTY(EditDefaultsOnly, Category = "E_S")
		class UAnimMontage* SheathBowMontage;

	UPROPERTY(EditDefaultsOnly, Category = "E_S")
		class UAnimMontage* EquipSpellMontage;

	UPROPERTY(EditDefaultsOnly, Category = "E_S")
		class UAnimMontage* SheathSpellMontage;

	UPROPERTY(EditDefaultsOnly, Category = "E_S")
		class UAnimMontage* EquipMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Motion")
		class UAnimMontage* SheathMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Motion")
		class UAnimMontage* ArrowDrawMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Motion")
		class UAnimMontage* ShoothMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Motion")
		class UAnimMontage* HitReractionMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Magic")
		class UAnimMontage* FireballMontage;
	UPROPERTY(EditDefaultsOnly, Category = "Magic")
		class UAnimMontage* FireballMontage2;
	UPROPERTY(EditDefaultsOnly, Category = "Magic")
		class UAnimMontage* FireballMontage3;

	UPROPERTY(EditDefaultsOnly, Category = "Dead")
		class UAnimMontage* DeadMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Motion")
		class UAnimMontage* Roll_F_Montage;

	UPROPERTY(EditDefaultsOnly, Category = "Motion")
		class UAnimMontage* Roll_B_Montage;

	UPROPERTY(EditDefaultsOnly, Category = "Motion")
		class UAnimMontage* Roll_R_Montage;

	UPROPERTY(EditDefaultsOnly, Category = "Motion")
		class UAnimMontage* Roll_L_Montage;

	UPROPERTY(EditDefaultsOnly, Category = "Motion")
		class UAnimMontage* Dash_F_Montage;

	UPROPERTY(EditDefaultsOnly, Category = "Motion")
		class UAnimMontage* Dash_B_Montage;

	UPROPERTY(EditDefaultsOnly, Category = "Motion")
		class UAnimMontage* Dash_R_Montage;

	UPROPERTY(EditDefaultsOnly, Category = "Motion")
		class UAnimMontage* Dash_L_Montage;


	UPROPERTY(EditDefaultsOnly, Category = "Particle")
		class UParticleSystem* Blood;


private:
	void UpdateAimAlpha();
	void UpdateBlock();
	void UpdateCrosshairPosition();
	void UpdateState();

	UPROPERTY(EditAnywhere)
		class UCurveFloat* CurveFloat;
public:
	UPROPERTY(BlueprintReadWrite)
		float Health; 
	UPROPERTY(BlueprintReadWrite)
		float Stamina;
	UPROPERTY(BlueprintReadWrite)
		float Mana;

public:
	bool GetDrawing() { return bDrawing; }
	bool GetSheathing() { return bSheathing; }
	E_State GetState() { return state; }
	E_CombatType GetCombatType() { return combatType; }
	E_WeaponType GetWeaponType() { return weaponType; }
	E_Activity GetActivity() { return activity; }
	E_MagicType GetMagicType() { return magicType; }

	bool GetShieldEquipped() { return bShieldEquipped; }
	float GetBlockAlpha() { return BlockAlpha; }
	float GetAimAlpha() { return AimAlpha; }

	class ACDisplayedItem* GetSword() { return CurrentItem; }
	class ACBlockAlpha* GetTimeline() { return timeline; }

	void GetAttackCount();
	
	float GetHealth() { return Health; }
	float GetStamina() { return Stamina; }
	float GetMana() { return Mana; }
	
	class UCameraComponent* GetFollowCamera() { return FollowCamera; }


private:
	void OnMoveForward(float Value);
	void OnMoveRight(float Value);
	void OnTurn(float Value);
	void OnLookUp(float Value);
	void OnZoom(float Value);
	void GoRight(float Value);
	void GoLeft(float Value);
	void GoUp(float Value);
	void GoDown(float Value);

	void OnRunning();
	void OffRunning();

	void OnJumping();
	void OnRolling();

	void OnEquip();
	void OnAttacking();
	void OffAttacking();

	void OnCharge();

	void OnBlocking();
	void OffBlocking();

	void OnAiming();
	void OffAiming();

	void OnMagic();
	void OnMagicNum1();
	void OnMagicNum2();
	void OnMagicNum3();
	void OnMagicNum4();
	void OnMagicNum5();
	void OnMagicChange();

	void OnFlying();
	void OffFlying();

	void Parrying();
	void BloodSpilt();
	void OnHitReaction();
	void OnCollision();

	void OnHuricain();
	void OffHuricain();
public:
	void OnSpawnArrow();
public:
	void OnDrawArrow();
	void SetCamera();
	void GetAttachCamera(AActor* Camera);
	void GetDetachCamera(AActor* Camera);
	float SideAxis;
	float UpAxis;
private:
	void Equip();
	void Sheath();
	void Roll();
public:
	void Equipped();
	void Sheathed();

	void BeginAttack();
	void EndAttack();

	void BeginBlock();
	void EndBlock();

	void ResetState();
	void Blocking();

	void OnShoot();
	void Dead();

	bool GetTest();

	float GetFoward;
	float GetRight;

	FVector WorldVector;

	void OnTargeting();
	
	UFUNCTION()
	void OnGrabRope(class ACRope* Rope);
	UFUNCTION()
	void OnUnGrabRope();

	bool GetGrabRope() { return bGrabRope; }
	class ACFallRespawn* FallRespawn;
private:
	bool bGrabRope;
	class USpringArmComponent* SpringArm;
	class ACGreateSword* Sword;
	class ACBlockAlpha* timeline;

	bool bCanMove = true;
	bool bAttacking = false;

	bool bForward;
	bool bRight;


	bool bDrawing;
	bool bSheathing;

	bool bDrawn;
	bool bRoll;
	bool bShieldEquipped;
	bool bBlock;
	bool bShoot;
	bool bImotal;
	//bool bCharge;

	int32 AttackCount;
	float BlockAlpha;
	float AimAlpha;


	E_State state;
	E_CombatType combatType;
	E_WeaponType weaponType;
	E_Activity activity;
	E_MagicType magicType;

	FTimeline Timeline;
	class ACRope* MyRope;

	bool bRuning;
	bool bstop;
	UFUNCTION()
		void TheWorld();
	
};

