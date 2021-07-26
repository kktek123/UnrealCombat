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
enum class E_EnemyType : uint8//적의 타입 집합
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

	//여러 행동종료를 AI에 전달
	FOnEndAttackDelegate OnEndAttack;
	FOnDeadDelegate OnDead;
	FOnAttackHitCheckDelegate OnAttackHitCheck;
protected:
	//엑터에 연결된 컴포넌트
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

	//각각의 애님몽타주

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
	//엑터에 있는 값주기
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
	//공격의 시작과 끝//애님노티파이에 사용
	void BeginAttack();
	void EndAttack();

	//void AttackCheck();
	//
	void Dead();//체력이 다했을때 죽음에 이릅니다.
	void Stun();//공격받을시 행동상태
	void ResetState();//캐릭터를 초기상태로 바꾼다.

	void OnAiming();//조준 상태
	void OffAiming();//조준 종료

	void SetCombatType(E_CombatType CombatType);//행동 타입 설정

	virtual FRotator GetDesireRotation();//현재 보고 있는 방향

	virtual bool OnDeselected();//TargetWidget숨기기
	virtual bool OnSelected();//TargetWidget보이기
	virtual bool IsTargetable();//타겟가능 여부
protected:

	class ACCombatCharacter* player;
	class ACSword* Sword;
	class ACDisplayedItem* DSword;//장착 아이템
	bool Blocking;
	bool bCanBlock;

	E_State state;//통상 상태

	UPROPERTY(EditAnywhere)
		E_EnemyType enemyType;
	//적의 타입설정

	EC_AIBehavior Behavior;//BehaviorTree 상태

	E_CombatType CombatType;//행동 상태

	UPROPERTY(EditAnywhere)//객체의 BehaviorTree
		class UBehaviorTree* BT;

	void HitReaction();//피격시 반응
	void BlockReaction();//가드시 반응
	void BloodSpilt();//피흘림
	void OnDeadAnimtion();//죽을시 반응

	bool IsActivityPure(E_Activity Activity);//누적 상태 설정

	void ResetTime();//느려진 시간을 회복

	//각각의 블루프린트 클래스 관리

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

	//엑션 타이머
	FTimeline Timeline;
	
	FTimerHandle CountdownTimerHandle;
	FTimerHandle HuricainTimerHandle;


	//FTimerHandle ShootTimerHandle;
	//FTimerHandle FallenTimerHandle;
	//FTimerHandle DamageTimerHandle;
	//FTimerHandle MagicTimerHandle;

	UPROPERTY(VisibleAnywhere)
		class UCurveFloat* CurveFloat;//자세변환 속도

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
	FRotator Target;//타겟의 방향

	ACSpawn* mySummon;//엑터의 소환위치
public:	
	virtual void Tick(float DeltaTime) override;


		UPROPERTY(EditAnywhere)
			AActor* CameraOne;

		UPROPERTY(EditAnywhere)
			AActor* CameraTwo;


	float TimeToNextCameraChange;

	FVector SpawnPoint;
	FVector DeadPoint;

	void MagicBoom();//마법 쏘기
	void ShootBoom();//폭탄 쏘기
	void Fallingboom();//폭탄 떨구기

	void SummonEnemy();//다른 엑터 소환

	void NormalShootBoom();//보통 폭탄 쏘기
	void NormalShootfireball();//파이어볼 쏘기
	bool bHeavyAttack;//특수 공격

	void OnJumping();//점프
	void OnWarp(FVector warpPoint);//위프해서 이동

	//마법 이펙트
	UPROPERTY(EditAnywhere)
		class UParticleSystem* WarpParticle;
	UPROPERTY(EditAnywhere)
		class UParticleSystem* MagicParticle;

	class ACSpellIndicator* SpellIndicator;//마법진

	UPROPERTY(EditAnywhere)
		uint32 MaxSpawnCount;//최대 소환 갯수
	uint32 SpawnedEnemyCount;//소환한 횟수

	void OnSpellIndicator(FVector MagicPoint);
	void OnMagic();

	void OnHeal();

	FVector SpellLocation;//마법위치

	bool bGetDamaged;

	UFUNCTION()
		void SetMySummon(ACSpawn* Summon);//소환체 선택
};
