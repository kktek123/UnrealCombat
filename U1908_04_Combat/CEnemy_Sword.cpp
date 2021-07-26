// Fill out your copyright notice in the Description page of Project Settings.


#include "CEnemy_Sword.h"
#include "Global.h"
#include "Item/CSword.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "CAIController.h"
#include "CCStateManager.h"
#include "CExtendedStamina.h"
#include "RotateComponent.h"
#include "MyGameProject/Item/CDisplayedItem.h"
#include "Components/WidgetComponent.h"
#include "CEnemyWidget.h"
#include "CHuricain.h"

ACEnemy_Sword::ACEnemy_Sword()
{
	PrimaryActorTick.bCanEverTick = true;

	FString path = L"BehaviorTree'/Game/Blueprints/BT.BT'";
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> bt(*path);
	if (bt.Succeeded())
		BT = bt.Object;

	 path = L"Blueprint'/Game/MyGameProjection/MyCDI_Hand1.MyCDI_Hand1_C'";
	ConstructorHelpers::FClassFinder<ACDisplayedItem> sword(*path);
	if (sword.Succeeded())
		ItemClass = sword.Class;

	path = L"AnimMontage'/Game/Enemy/Armed_Attack_Montage.Armed_Attack_Montage'";
	ConstructorHelpers::FObjectFinder<UAnimMontage> attack(*path);
	if (attack.Succeeded())
		AttackMontage = attack.Object;

	path = L"AnimMontage'/Game/1HS_SpecialAttack_02_Montage.1HS_SpecialAttack_02_Montage'";
	ConstructorHelpers::FObjectFinder<UAnimMontage> hattack(*path);
	if (hattack.Succeeded())
		HeavyAttackMontage = hattack.Object;



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



	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel1, ECollisionResponse::ECR_Block);

}

void ACEnemy_Sword::BeginPlay()
{
	Super::BeginPlay();
	bCanBlock = true;
	enemyType = E_EnemyType::SwordMan;
	FTransform transform = FTransform::Identity;
	FActorSpawnParameters params;
	params.Owner = this;

	Cast<UCEnemyWidget>(StateWidget->GetUserWidgetObject())->enemy = this;

	//GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ACEnemy::OnBegin);
	//GetCapsuleComponent()->OnComponentEndOverlap.AddDynamic(this, &ACEnemy::OnEnd);

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ACEnemy_Sword::OnBegin);
	GetCapsuleComponent()->OnComponentEndOverlap.AddDynamic(this, &ACEnemy_Sword::OnEnd);


	RetNull(ItemClass);
	DSword = GetWorld()->SpawnActor<ACDisplayedItem>(ItemClass, transform, params);
	DSword->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), "sword_use");


}

void ACEnemy_Sword::TakeDamage()
{
	Super::TakeDamage();
}


void ACEnemy_Sword::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACEnemy_Sword::OnBegin(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	//CLog::Print(TEXT("OnBegin"));
	RetNull(OtherActor);
	RetNull(OtherComp);
	if (OtherActor == this)return;

	if (OtherActor->GetClass()->IsChildOf(ACHuricain::StaticClass()))
	{
		//CLog::Print(TEXT("OnBegin"));
		Huricain = Cast<ACHuricain>(OtherActor);
		GetWorldTimerManager().SetTimer(HuricainTimerHandle, this, &ACEnemy_Sword::TakeDamage, 0.5f, true);

	}

}

void ACEnemy_Sword::OnEnd(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	RetNull(OtherActor);
	RetNull(OtherComp);
	if (OtherActor == this)return;

	if (Huricain != NULL)
		Huricain = NULL;
	GetWorldTimerManager().ClearTimer(HuricainTimerHandle);

}
