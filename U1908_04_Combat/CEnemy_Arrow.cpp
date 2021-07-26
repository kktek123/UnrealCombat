// Fill out your copyright notice in the Description page of Project Settings.


#include "CEnemy_Arrow.h"
#include "Global.h"
#include "Item/CSword.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "CAIController.h"
#include "CCStateManager.h"
#include "CExtendedStamina.h"
#include "RotateComponent.h"
#include "MyGameProject/Item/CDisplayedItem.h"
#include "MyGameProject/Item/CArrow.h"
#include "Components/WidgetComponent.h"
#include "CEnemyWidget.h"
#include "CHuricain.h"

ACEnemy_Arrow::ACEnemy_Arrow()
{
	PrimaryActorTick.bCanEverTick = true;

	FString path = L"BehaviorTree'/Game/Blueprints/BT1.BT1'";
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> bt(*path);
	if (bt.Succeeded())
		BT = bt.Object;

	 path = L"BlueprintGeneratedClass'/Game/MyGameProjection/MyCDI_Bow.MyCDI_Bow_C'";
	ConstructorHelpers::FClassFinder<ACDisplayedItem> sword(*path);
	if (sword.Succeeded())
		ItemClass = sword.Class;

	path = L"AnimMontage'/Game/MyPortpol/Animation/PlayerAnimation/AR_ShootAndDraw_Montage.AR_ShootAndDraw_Montage'";
	ConstructorHelpers::FObjectFinder<UAnimMontage> attack(*path);
	if (attack.Succeeded())
		AttackMontage = attack.Object;

	path = L"AnimMontage'/Game/MyPortpol/Animation/PlayerAnimation/AR_ShootAndDraw_Montage.AR_ShootAndDraw_Montage'";
	ConstructorHelpers::FObjectFinder<UAnimMontage> range(*path);
	if (range.Succeeded())
		RangeAttackMontage = range.Object;


	path = L"AnimMontage'/Game/MyPortpol/Animation/PlayerAnimation/1HandSwordAndShield/Frank_RPG_Warrior_Hit01_Montage.Frank_RPG_Warrior_Hit01_Montage'";
	ConstructorHelpers::FObjectFinder<UAnimMontage> hit(*path);
	if (hit.Succeeded())
		HitReactionMontage = hit.Object;

	path = L"AnimMontage'/Game/MyPortpol/Animation/PlayerAnimation/1HandSwordAndShield/Frank_RPG_Warrior_Hit_Knockdown_Montage.Frank_RPG_Warrior_Hit_Knockdown_Montage'";
	ConstructorHelpers::FObjectFinder<UAnimMontage> dead(*path);
	if (dead.Succeeded())
		DeadMontage = dead.Object;

	//path = L"ParticleSystem'/Game/Particles/PS_Blood_Splatter.PS_Blood_Splatter'";
	//ConstructorHelpers::FObjectFinder<UParticleSystem> blood(*path);
	//if (blood.Succeeded())
	//	Blood = blood.Object;

	path = L"SoundCue'/Game/DynamicCombatSystem/SFX/CUE/Cue_HitSword.CUE_HitSword'";
	ConstructorHelpers::FObjectFinder<USoundBase> pain(*path);
	if (pain.Succeeded())
		PainSound = pain.Object;

	//ArrowLocation
	{
		//path = L"Blueprint'/Game/Item/MyCArrow.MyCArrow2_C'";
		//ConstructorHelpers::FClassFinder<ACArrow> arrow(*path);
		//if (arrow.Succeeded())
		//	ArrowClass = arrow.Class;

		ArrowLocation = CreateDefaultSubobject<USceneComponent>(TEXT("ArrowLocation"));
		ArrowLocation->SetupAttachment(GetMesh(), L"bow_string");

		ArrowShootLocation = CreateDefaultSubobject<USceneComponent>(TEXT("ArrowShootLocation"));
		ArrowShootLocation->SetupAttachment(GetMesh(), L"bow_shoot");

	}
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel1, ECollisionResponse::ECR_Block);

}

void ACEnemy_Arrow::BeginPlay()
{
	Super::BeginPlay();
	bCanBlock = false;
	enemyType = E_EnemyType::Archer;
	FTransform transform = FTransform::Identity;
	FActorSpawnParameters params;
	params.Owner = this;

	Cast<UCEnemyWidget>(StateWidget->GetUserWidgetObject())->enemy = this;

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ACEnemy_Arrow::OnBegin);
	GetCapsuleComponent()->OnComponentEndOverlap.AddDynamic(this, &ACEnemy_Arrow::OnEnd);

	bShooted = true;

	RetNull(ItemClass);
	DSword = GetWorld()->SpawnActor<ACDisplayedItem>(ItemClass, transform, params);
	DSword->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), "bow_use");

}

void ACEnemy_Arrow::TakeDamage()
{
	Super::TakeDamage();

}


void ACEnemy_Arrow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsActivityPure(E_Activity::IsAimingPressed))
	{
		AimAlpha = FMath::FInterpConstantTo(AimAlpha, 1.0f, UGameplayStatics::GetWorldDeltaSeconds(this), 3.0f);
		//state = E_State::Attacking;
	}
	else
	{
		AimAlpha = FMath::FInterpConstantTo(AimAlpha, 0.0f, UGameplayStatics::GetWorldDeltaSeconds(this), 3.0f);
		OnEndAttack.Broadcast();
	}
	if (AimAlpha >= 1)
	{
		fString += DeltaTime;
		if (fString >= 5)
			bShoot = true;
	}
	else
	{
		bShoot = false;
		fString = 0;
		//GetWorldTimerManager().ClearTimer(CountdownTimerHandle);
		//GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
	}

	if (bShoot)
	{
		StateManager->SetActivity(E_Activity::IsAimingPressed, false);
		PlayAnimMontage(RangeAttackMontage, 1.5f);
		ExtendedStamina->ModifyStat(-40, true);
		fString = 0;
		bShooted = true;
	}
}
void ACEnemy_Arrow::OnString()
{
	if (bString)
	GetWorldTimerManager().SetTimer(CountdownTimerHandle, this, &ACEnemy_Arrow::OnShoot, 3.0f, false);
}
void ACEnemy_Arrow::OnShoot()
{
	
}

void ACEnemy_Arrow::OnBegin(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	//CLog::Print(TEXT("OnBegin"));
	RetNull(OtherActor);
	RetNull(OtherComp);
	if (OtherActor == this)return;

	if (OtherActor->GetClass()->IsChildOf(ACHuricain::StaticClass()))
	{
		//CLog::Print(TEXT("OnBegin"));
		Huricain = Cast<ACHuricain>(OtherActor);
		GetWorldTimerManager().SetTimer(HuricainTimerHandle, this, &ACEnemy_Arrow::TakeDamage, 0.2f, true);

	}

}

void ACEnemy_Arrow::OnEnd(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	RetNull(OtherActor);
	RetNull(OtherComp);
	if (OtherActor == this)return;

	if (Huricain != NULL)
		Huricain = NULL;
	GetWorldTimerManager().ClearTimer(HuricainTimerHandle);

}