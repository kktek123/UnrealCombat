// Fill out your copyright notice in the Description page of Project Settings.


#include "CEnemy_Boss.h"
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
#include "CAudioActor.h"


ACEnemy_Boss::ACEnemy_Boss()
{
	PrimaryActorTick.bCanEverTick = true;

	FString path = L"BehaviorTree'/Game/Blueprints/BT2.BT2'";
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> bt(*path);
	if (bt.Succeeded())
		BT = bt.Object;

	 path = L"Blueprint'/Game/MyGameProjection/MyCDI_Hand2.MyCDI_Hand2_C'";
	ConstructorHelpers::FClassFinder<ACDisplayedItem> sword(*path);
	if (sword.Succeeded())
		ItemClass = sword.Class;

	path = L"AnimMontage'/Game/Boss/ExoGame_Troll_Attack_Montage.ExoGame_Troll_Attack_Montage'";
	ConstructorHelpers::FObjectFinder<UAnimMontage> attack(*path);
	if (attack.Succeeded())
		AttackMontage = attack.Object;

	path = L"AnimMontage'/Game/Boss/ExoGame_MasterGrunt_Attack_Melee_B_Montage.ExoGame_MasterGrunt_Attack_Melee_B_Montage'";
	ConstructorHelpers::FObjectFinder<UAnimMontage> hattack(*path);
	if (hattack.Succeeded())
		HeavyAttackMontage = hattack.Object;

	path = L"AnimMontage'/Game/Boss/ExoGame_MasterGrunt_Attack_Ranged_Montage.ExoGame_MasterGrunt_Attack_Ranged_Montage'";
	ConstructorHelpers::FObjectFinder<UAnimMontage> range(*path);
	if (range.Succeeded())
		RangeAttackMontage = range.Object;

	path = L"AnimMontage'/Game/Boss/ExoGame_MasterGrunt_Cast_Summon_Montage.ExoGame_MasterGrunt_Cast_Summon_Montage'";
	ConstructorHelpers::FObjectFinder<UAnimMontage> magic(*path);
	if (magic.Succeeded())
		MagicAttackMontage = magic.Object;

	path = L"AnimMontage'/Game/Boss/ExoGame_MasterGrunt_React_Light_Front_Montage.ExoGame_MasterGrunt_React_Light_Front_Montage'";
	ConstructorHelpers::FObjectFinder<UAnimMontage> hit(*path);
	if (hit.Succeeded())
		HitReactionMontage = hit.Object;

	path = L"AnimMontage'/Game/Boss/ExoGame_MasterGrunt_Death_Montage.ExoGame_MasterGrunt_Death_Montage'";
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
		path = L"Blueprint'/Game/Item/MyCArrow3.MyCArrow3_C'";
		ConstructorHelpers::FClassFinder<ACArrow> arrow(*path);
		if (arrow.Succeeded())
			ArrowClass = arrow.Class;

		ArrowLocation = CreateDefaultSubobject<USceneComponent>(TEXT("ArrowLocation"));
		ArrowLocation->SetupAttachment(GetMesh(), L"Shootboom");

		ArrowShootLocation = CreateDefaultSubobject<USceneComponent>(TEXT("ArrowShootLocation"));
		ArrowShootLocation->SetupAttachment(GetMesh(), L"Shootboom");

	}

	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel1, ECollisionResponse::ECR_Block);
	GetCapsuleComponent()->SetCollisionObjectType(ECollisionChannel::ECC_EngineTraceChannel2);
	GetMesh()->SetCollisionObjectType(ECollisionChannel::ECC_EngineTraceChannel2);

}

void ACEnemy_Boss::BeginPlay()
{
	Super::BeginPlay();

	enemyType = E_EnemyType::Master;
	FTransform transform = FTransform::Identity;
	FActorSpawnParameters params;
	params.Owner = this;

	Cast<UCEnemyWidget>(StateWidget->GetUserWidgetObject())->enemy = this;

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ACEnemy_Boss::OnBegin);
	GetCapsuleComponent()->OnComponentEndOverlap.AddDynamic(this, &ACEnemy_Boss::OnEnd);

	RetNull(ItemClass);
	DSword = GetWorld()->SpawnActor<ACDisplayedItem>(ItemClass, transform, params);
	DSword->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), "Weapon_R");


	RetNull(audioClass);
	if (enemyType == E_EnemyType::Master)
	{
		audio = GetWorld()->SpawnActor<ACAudioActor>(audioClass, transform, params);
		audio->PlayMusic(2);

	}
}

void ACEnemy_Boss::TakeDamage()
{
	Super::TakeDamage();
}


void ACEnemy_Boss::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
}
void ACEnemy_Boss::OnString()
{
	CLog::Print(TEXT("OnString"));
	if (bString)
	GetWorldTimerManager().SetTimer(CountdownTimerHandle, this, &ACEnemy_Boss::OnShoot, 3.0f, false);
}
void ACEnemy_Boss::OnShoot()
{
	
}

void ACEnemy_Boss::OnBegin(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	//CLog::Print(TEXT("OnBegin"));
	RetNull(OtherActor);
	RetNull(OtherComp);
	if (OtherActor == this)return;

	if (OtherActor->GetClass()->IsChildOf(ACHuricain::StaticClass()))
	{
		//CLog::Print(TEXT("OnBegin"));
		Huricain = Cast<ACHuricain>(OtherActor);
		GetWorldTimerManager().SetTimer(HuricainTimerHandle, this, &ACEnemy_Boss::TakeDamage, 0.5f, true);

	}

}

void ACEnemy_Boss::OnEnd(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	RetNull(OtherActor);
	RetNull(OtherComp);
	if (OtherActor == this)return;

	if (Huricain != NULL)
		Huricain = NULL;
	GetWorldTimerManager().ClearTimer(HuricainTimerHandle);

}