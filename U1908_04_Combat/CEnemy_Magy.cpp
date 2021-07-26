// Fill out your copyright notice in the Description page of Project Settings.


#include "CEnemy_Magy.h"
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


ACEnemy_Magy::ACEnemy_Magy()
{
	PrimaryActorTick.bCanEverTick = true;
	FString path;
	path = L"BehaviorTree'/Game/Blueprints/BT5.BT5'";
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> bt(*path);
	if (bt.Succeeded())
		BT = bt.Object;

	path = L"Blueprint'/Game/MyGameProjection/MyCDI_Hand4.MyCDI_Hand4_C'";
	ConstructorHelpers::FClassFinder<ACDisplayedItem> sword(*path);
	if (sword.Succeeded())
		ItemClass = sword.Class;

	path = L"AnimMontage'/Game/Magy/Frank_RPG_Warrior_Combo03_2_IP_Montage.Frank_RPG_Warrior_Combo03_2_IP_Montage'";
	ConstructorHelpers::FObjectFinder<UAnimMontage> attack(*path);
	if (attack.Succeeded())
		AttackMontage = attack.Object;

	path = L"AnimMontage'/Game/Magy/Frank_RPG_Warrior_Combo03_All_Montage.Frank_RPG_Warrior_Combo03_All_Montage'";
	ConstructorHelpers::FObjectFinder<UAnimMontage> hattack(*path);
	if (hattack.Succeeded())
		HeavyAttackMontage = hattack.Object;

	path = L"AnimMontage'/Game/MyPortpol/Animation/PlayerAnimation/Magic/MG_Fireball_02_Montage.MG_Fireball_02_Montage'";
	ConstructorHelpers::FObjectFinder<UAnimMontage> range(*path);
	if (range.Succeeded())
		RangeAttackMontage = range.Object;

	path = L"AnimMontage'/Game/Magy/MG_InfernoAttack_Montage.MG_InfernoAttack_Montage'";
	ConstructorHelpers::FObjectFinder<UAnimMontage> magic(*path);
	if (magic.Succeeded())
		MagicAttackMontage = magic.Object;

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
		path = L"Blueprint'/Game/Item/MyCArrow3.MyCArrow3_C'";
		ConstructorHelpers::FClassFinder<ACArrow> arrow(*path);
		if (arrow.Succeeded())
			ArrowClass = arrow.Class;

		ArrowLocation = CreateDefaultSubobject<USceneComponent>(TEXT("ArrowLocation"));
		ArrowLocation->SetupAttachment(GetMesh(), L"Shootboom");

		ArrowShootLocation = CreateDefaultSubobject<USceneComponent>(TEXT("ArrowShootLocation"));
		ArrowShootLocation->SetupAttachment(GetMesh(), L"Weapon_L");

	}

	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel1, ECollisionResponse::ECR_Block);
	GetCapsuleComponent()->SetCollisionObjectType(ECollisionChannel::ECC_EngineTraceChannel2);
	GetMesh()->SetCollisionObjectType(ECollisionChannel::ECC_EngineTraceChannel2);

}

void ACEnemy_Magy::BeginPlay()
{
	Super::BeginPlay();
	bCanBlock = true;
	enemyType = E_EnemyType::Magy;
	FTransform transform = FTransform::Identity;
	FActorSpawnParameters params;
	params.Owner = this;

	Cast<UCEnemyWidget>(StateWidget->GetUserWidgetObject())->enemy = this;

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ACEnemy_Magy::OnBegin);
	GetCapsuleComponent()->OnComponentEndOverlap.AddDynamic(this, &ACEnemy_Magy::OnEnd);

	RetNull(ItemClass);
	DSword = GetWorld()->SpawnActor<ACDisplayedItem>(ItemClass, transform, params);
	DSword->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), "hand_rSocket");

}

void ACEnemy_Magy::TakeDamage()
{
	Super::TakeDamage();
}


void ACEnemy_Magy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}
void ACEnemy_Magy::OnString()
{
	//CLog::Print(TEXT("OnString"));
	if (bString)
		GetWorldTimerManager().SetTimer(CountdownTimerHandle, this, &ACEnemy_Magy::OnShoot, 3.0f, false);
}
void ACEnemy_Magy::OnShoot()
{

}

void ACEnemy_Magy::OnBegin(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	//CLog::Print(TEXT("OnBegin"));
	RetNull(OtherActor);
	RetNull(OtherComp);
	if (OtherActor == this)return;

	if (OtherActor->GetClass()->IsChildOf(ACHuricain::StaticClass()))
	{
		//CLog::Print(TEXT("OnBegin"));
		Huricain = Cast<ACHuricain>(OtherActor);
		GetWorldTimerManager().SetTimer(HuricainTimerHandle, this, &ACEnemy_Magy::TakeDamage, 0.5f, true);

	}

}

void ACEnemy_Magy::OnEnd(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	RetNull(OtherActor);
	RetNull(OtherComp);
	if (OtherActor == this)return;

	if (Huricain != NULL)
		Huricain = NULL;
	GetWorldTimerManager().ClearTimer(HuricainTimerHandle);

}
