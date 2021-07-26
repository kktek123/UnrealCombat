// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "UIRotate.h"
#include "UITargetable.h"
#include "Enums/CEnum0.h"
#include "Components/TimelineComponent.h"
#include "CAIController.h"
#include "CSpawn.h"
#include "CEnemy.generated.h"

UENUM(BlueprintType)
enum class E_EnemyType : uint8//���� Ÿ�� ����
{
	Pawn UMETA(DisplayName = "Pawn"),
	SwordMan UMETA(DisplayName = "SwordMan"),
	Archer UMETA(DisplayName = "Archer"),
	Master UMETA(DisplayName = "Master"),
	Warrok UMETA(DisplayName = "Warrok"),
	Barghest UMETA(DisplayName = "Barghest"),
	Drangon UMETA(DisplayName = "Drangon"),
	Magy UMETA(DisplayName = "Magy"),
};

DECLARE_MULTICAST_DELEGATE(FOnEndAttackDelegate)
DECLARE_MULTICAST_DELEGATE(FOnDeadDelegate)
DECLARE_MULTICAST_DELEGATE(FOnAttackHitCheckDelegate)

UCLASS()
class U1908_04_COMBAT_API ACEnemy : public ACharacter, public IUIRotate,public IUITargetable
{
	GENERATED_BODY()

public:
	ACEnemy();

	//���� �ൿ���Ḧ AI�� ����
	FOnEndAttackDelegate OnEndAttack;
	FOnDeadDelegate OnDead;
	FOnAttackHitCheckDelegate OnAttackHitCheck;
protected:
	//���Ϳ� ����� ������Ʈ
	UPROPERTY(VisibleAnywhere)
		class UCameraComponent* CineCamera;

	UPROPERTY(VisibleAnywhere)
		class UCameraComponent* CineCamera2;

	UPROPERTY(VisibleAnywhere)
		class UCameraComponent* CineCamera3;

	UPROPERTY(VisibleAnywhere)
		class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere)
		class UWidgetComponent* StateWidget;

	UPROPERTY(VisibleAnywhere)
		class UWidgetComponent* TargetWidget;

	UPROPERTY(VisibleAnywhere)
		class UCEnemyWidget* Widget;

	UPROPERTY(VisibleAnywhere)
		class UCCStateManager* StateManager;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UCExtendedStamina* ExtendedStamina;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UCExtendedStamina* ExtendedHealth;

	UPROPERTY(VisibleAnywhere)
		class URotateComponent* RotateComponent;

	UPROPERTY(EditAnywhere)
		class USoundBase* PainSound;

	UPROPERTY(EditAnywhere)
		class USoundBase* BlockSound;

	//������ �ִԸ�Ÿ��

	UPROPERTY(EditDefaultsOnly, Category = "Melee")
		class UAnimMontage* AttackMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Melee")
		class UAnimMontage* HeavyAttackMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Range")
		class UAnimMontage* RangeAttackMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Magic")
		class UAnimMontage* MagicAttackMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Magic")
		class UAnimMontage* MagicSummonMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Motion")
		class UAnimMontage* HitReactionMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Motion")
		class UAnimMontage* BlockReactionMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Motion")
		class UAnimMontage* DeadMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Motion")
		class UAnimMontage* StunMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Particle")
		class UParticleSystem* Blood;

	UPROPERTY(EditDefaultsOnly, Category = "audio")
		TSubclassOf<class ACAudioActor> audioClass;

	UPROPERTY(EditDefaultsOnly, Category = "Magic")
		TSubclassOf<class ACSpellIndicator> MagicClass;


	//UPROPERTY(EditDefaultsOnly, Category = "audio")
		class ACAudioActor* audio;

public:
	//���Ϳ� �ִ� ���ֱ�
	class ACDisplayedItem* GetSword() { return DSword; }
	E_EnemyType GetEnemyType() { return enemyType; }
	E_State GetState() { return state; }
	EC_AIBehavior GetBehavior() { return Behavior; }
	E_CombatType GetCombatType() { return CombatType; }
	
	APlayerController* OurPlayerController;

	bool GetBlocking() { return Blocking; }

	class UCCStateManager* GetStateManager() { return StateManager; }

	class UCExtendedStamina* GetExtendedStamina() { return ExtendedStamina; }
	
	class UCExtendedStamina* GetExtendedHealth() { return ExtendedHealth; }

	class URotateComponent* GetRotateComponent() { return RotateComponent; }

	class UBehaviorTree* GetBT() { return BT; }

	float GetAimAlpha() { return AimAlpha; }

	bool bLastOne;


	UPROPERTY(EditAnywhere)
		float Hp;
	//
public:
	//������ ���۰� ��//�ִԳ�Ƽ���̿� ���
	void BeginAttack();
	void EndAttack();

	//void AttackCheck();
	//
	void Dead();//ü���� �������� ������ �̸��ϴ�.
	void Stun();//���ݹ����� �ൿ����
	void ResetState();//ĳ���͸� �ʱ���·� �ٲ۴�.

	void OnAiming();//���� ����
	void OffAiming();//���� ����

	void SetCombatType(E_CombatType CombatType);//�ൿ Ÿ�� ����

	virtual FRotator GetDesireRotation();//���� ���� �ִ� ����

	virtual bool OnDeselected();//TargetWidget�����
	virtual bool OnSelected();//TargetWidget���̱�
	virtual bool IsTargetable();//Ÿ�ٰ��� ����
protected:

	class ACCombatCharacter* player;
	class ACSword* Sword;
	class ACDisplayedItem* DSword;//���� ������
	bool Blocking;
	bool bCanBlock;

	E_State state;//��� ����

	UPROPERTY(EditAnywhere)
		E_EnemyType enemyType;
	//���� Ÿ�Լ���

	EC_AIBehavior Behavior;//BehaviorTree ����

	E_CombatType CombatType;//�ൿ ����

	UPROPERTY(EditAnywhere)//��ü�� BehaviorTree
		class UBehaviorTree* BT;

	void HitReaction();//�ǰݽ� ����
	void BlockReaction();//����� ����
	void BloodSpilt();//���긲
	void OnDeadAnimtion();//������ ����

	bool IsActivityPure(E_Activity Activity);//���� ���� ����

	void ResetTime();//������ �ð��� ȸ��

	//������ �������Ʈ Ŭ���� ����

	UPROPERTY(EditDefaultsOnly, Category = "Widget")
		TSubclassOf<class UUserWidget> WidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "Widget")
		TSubclassOf<class UUserWidget> TargetWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
		TSubclassOf<class ACSword> SwordClass;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
		TSubclassOf<class ACDisplayedItem> ItemClass;

	UPROPERTY(EditAnywhere, Category = "Arrow")
		TSubclassOf<class ACArrow> ArrowClass;

	UPROPERTY(EditAnywhere, Category = "Boom")
		TSubclassOf<class ACBoom> ShootBoomClass;

	UPROPERTY(EditAnywhere, Category = "Boom")
		TSubclassOf<class ACBoom> NormalBoomClass;

	UPROPERTY(EditAnywhere, Category = "Boom")
		TSubclassOf<class ACBoom> BoomClass;

	UPROPERTY(EditAnywhere, Category = "Summon")
		TSubclassOf<class ACSpawn> SpawnClass;

	UPROPERTY(EditAnywhere, Category = "Summon")
		TSubclassOf<class ACEnemy> SummonClass;

	UPROPERTY(EditAnywhere, Category = "Spell")
		TSubclassOf<class ACFireball> FireballClass;


	UPROPERTY(EditAnywhere, Category = "summpoiont")
		float Summonpoint;

	UPROPERTY(VisibleAnywhere)
		class USceneComponent* ArrowLocation;

	UPROPERTY(VisibleAnywhere)
		class USceneComponent* ArrowShootLocation;

	class ACArrow* Arrow;
	class ACBoom* Boom;

	void UpdateFlightTimeline(UCurveFloat * CurveFloat);

	//���� Ÿ�̸�
	FTimeline Timeline;
	
	FTimerHandle CountdownTimerHandle;
	FTimerHandle HuricainTimerHandle;


	//FTimerHandle ShootTimerHandle;
	//FTimerHandle FallenTimerHandle;
	//FTimerHandle DamageTimerHandle;
	//FTimerHandle MagicTimerHandle;

	UPROPERTY(VisibleAnywhere)
		class UCurveFloat* CurveFloat;//�ڼ���ȯ �ӵ�

	float AimAlpha;
	bool bString;
	bool bShoot;
	bool bShooted;
	class ACHuricain* Huricain;

	UPROPERTY(EditAnywhere)
		ACAIController* AIController;

protected:
	virtual void BeginPlay() override;

	virtual float TakeDamage(float Damage, struct FDamageEvent 
		const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	virtual void TakeDamage();

	UPROPERTY(EditAnywhere)
		float Damage = 10;
	FRotator Target;//Ÿ���� ����

	ACSpawn* mySummon;//������ ��ȯ��ġ
public:	
	virtual void Tick(float DeltaTime) override;


		UPROPERTY(EditAnywhere)
			AActor* CameraOne;

		UPROPERTY(EditAnywhere)
			AActor* CameraTwo;


	float TimeToNextCameraChange;

	FVector SpawnPoint;
	FVector DeadPoint;

	void MagicBoom();//���� ���
	void ShootBoom();//��ź ���
	void Fallingboom();//��ź ������

	void SummonEnemy();//�ٸ� ���� ��ȯ

	void NormalShootBoom();//���� ��ź ���
	void NormalShootfireball();//���̾ ���
	bool bHeavyAttack;//Ư�� ����

	void OnJumping();//����
	void OnWarp(FVector warpPoint);//�����ؼ� �̵�

	//���� ����Ʈ
	UPROPERTY(EditAnywhere)
		class UParticleSystem* WarpParticle;
	UPROPERTY(EditAnywhere)
		class UParticleSystem* MagicParticle;

	class ACSpellIndicator* SpellIndicator;//������

	UPROPERTY(EditAnywhere)
		uint32 MaxSpawnCount;//�ִ� ��ȯ ����
	uint32 SpawnedEnemyCount;//��ȯ�� Ƚ��

	void OnSpellIndicator(FVector MagicPoint);
	void OnMagic();

	void OnHeal();

	FVector SpellLocation;//������ġ

	bool bGetDamaged;

	UFUNCTION()
		void SetMySummon(ACSpawn* Summon);//��ȯü ����
};
