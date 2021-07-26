// Fill out your copyright notice in the Description page of Project Settings.


#include "CEnemy_Fly.h"
#include "Global.h"
#include "Item/CSword.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "CFlyingAIController.h"
#include "CCStateManager.h"
#include "CExtendedStamina.h"
#include "RotateComponent.h"
#include "MyGameProject/Item/CDisplayedItem.h"
#include "MyGameProject/Item/CArrow.h"
#include "Components/WidgetComponent.h"
#include "CEnemyWidget.h"
#include "CHuricain.h"

ACEnemy_Fly::ACEnemy_Fly()
{
	FString path = L"BehaviorTree'/Game/Blueprints/BT3.BT3'";
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> bt(*path);
	if (bt.Succeeded())
		BT = bt.Object;



	path = L"AnimMontage'/Game/MyPortpol/Animation/PlayerAnimation/AR_ShootAndDraw_Montage.AR_ShootAndDraw_Montage'";
	ConstructorHelpers::FObjectFinder<UAnimMontage> attack(*path);
	if (attack.Succeeded())
		AttackMontage = attack.Object;

	path = L"AnimMontage'/Game/Fly/FlyAttackAnim_Montage.FlyAttackAnim_Montage'";
	ConstructorHelpers::FObjectFinder<UAnimMontage> range(*path);
	if (range.Succeeded())
		RangeAttackMontage = range.Object;


	//path = L"AnimMontage'/Game/MyPortpol/Animation/PlayerAnimation/1HandSwordAndShield/Frank_RPG_Warrior_Hit01_Montage.Frank_RPG_Warrior_Hit01_Montage'";
	//ConstructorHelpers::FObjectFinder<UAnimMontage> hit(*path);
	//if (hit.Succeeded())
	//	HitReactionMontage = hit.Object;

	path = L"AnimMontage'/Game/Fly/DieAnim_Montage.DieAnim_Montage'";
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
		//path = L"Blueprint'/Game/Item/MyCArrow3.MyCArrow3_C'";
		//ConstructorHelpers::FClassFinder<ACArrow> arrow(*path);
		//if (arrow.Succeeded())
		//	ArrowClass = arrow.Class;

		ArrowLocation = CreateDefaultSubobject<USceneComponent>(TEXT("ArrowLocation"));
		ArrowLocation->SetupAttachment(GetMesh(), L"Shootfire");

		ArrowShootLocation = CreateDefaultSubobject<USceneComponent>(TEXT("ArrowShootLocation"));
		ArrowShootLocation->SetupAttachment(GetMesh(), L"Shootfire");

	}
	//GetActorLocation();
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel1, ECollisionResponse::ECR_Block);

}

void ACEnemy_Fly::BeginPlay()
{
	Super::BeginPlay();

	enemyType = E_EnemyType::Drangon;
	FTransform transform = FTransform::Identity;
	FActorSpawnParameters params;
	params.Owner = this;

	Cast<UCEnemyWidget>(StateWidget->GetUserWidgetObject())->enemy = this;

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ACEnemy_Fly::OnBegin);
	GetCapsuleComponent()->OnComponentEndOverlap.AddDynamic(this, &ACEnemy_Fly::OnEnd);

	GetCharacterMovement()->DefaultLandMovementMode = EMovementMode::MOVE_Flying;
	GetCharacterMovement()->MaxWalkSpeed = 500;
}

void ACEnemy_Fly::TakeDamage()
{
	Super::TakeDamage();

}

void ACEnemy_Fly::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACEnemy_Fly::Progress(float Value)
{
	//BlockAlpha = 100 * CurveFloat->GetFloatValue(Value);
}

void ACEnemy_Fly::ResetProgress()
{
}

void ACEnemy_Fly::UpdateFlightTimeline(UCurveFloat * CurveFloat)
{
	Timeline = FTimeline();//Timeline초기화

	FOnTimelineFloat progress;
	progress.BindUFunction(this, "Progress");

	Timeline.AddInterpFloat(CurveFloat, progress);
	Timeline.SetLooping(false);
	Timeline.SetTimelineLengthMode(TL_LastKeyFrame);


	FOnTimelineEvent timelineEvent;//
	timelineEvent.BindUFunction(this, "ResetProgress");//리셋
	Timeline.SetTimelineFinishedFunc(timelineEvent);//상황에따라 이벤트 콜
}

void ACEnemy_Fly::OnBegin(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	RetNull(OtherActor);
	RetNull(OtherComp);
	if (OtherActor == this)return;

	if (OtherActor->GetClass()->IsChildOf(ACHuricain::StaticClass()))
	{
		Huricain = Cast<ACHuricain>(OtherActor);
		GetWorldTimerManager().SetTimer(HuricainTimerHandle, this, &ACEnemy_Fly::TakeDamage, 0.2f, true);

	}

}

void ACEnemy_Fly::OnEnd(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	RetNull(OtherActor);
	RetNull(OtherComp);
	if (OtherActor == this)return;

	if (Huricain != NULL)
		Huricain = NULL;
	GetWorldTimerManager().ClearTimer(HuricainTimerHandle);

}