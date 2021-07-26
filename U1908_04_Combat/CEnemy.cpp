// Fill out your copyright notice in the Description page of Project Settings.


#include "CEnemy.h"
#include "Global.h"
#include "Item/CSword.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "CAIController.h"
#include "CCStateManager.h"
#include "CExtendedStamina.h"
#include "RotateComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "CineCameraComponent.h"
#include "CCombatCharacter.h"
#include "DeadCineCameraActor.h"
#include "Components/WidgetComponent.h"
#include "CEnemyWidget.h"
#include "CHuricain.h"
#include "MyGameProject/Item/CDisplayedItem.h"
#include "MyGameProject/Item/CArrow.h"
#include "CAudioActor.h"
#include "CSpellIndicator.h"


ACEnemy::ACEnemy()
{
	PrimaryActorTick.bCanEverTick = true;
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	//GetCharacterMovement()->MaxWalkSpeed = 400.0f;
	FString path = L"Blueprint'/Game/Item/BpCSword.BpCSword_C'";
	ConstructorHelpers::FClassFinder<ACSword> sword(*path);
	if (sword.Succeeded())
		SwordClass = sword.Class;

	//path = L"Blueprint'/Game/MyDeadCineCameraActor.MyDeadCineCameraActor_C'";
	//ConstructorHelpers::FObjectFinder<ADeadCineCameraActor> ca(*path);
	//if (ca.Succeeded())
	//	CameraOne = ca.Object;
	//DDB

	path = L"CurveFloat'/Game/MyGameProjection/Alpha/BlockAlpha.BlockAlpha'";
	ConstructorHelpers::FObjectFinder<UCurveFloat> curve(*path);
	if (curve.Succeeded())
		CurveFloat = curve.Object;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->bUsePawnControlRotation = true;
	CameraBoom->SetupAttachment(GetMesh());

	path = L"WidgetBlueprint'/Game/Enemy/BpCEnemyWidget1.BpCEnemyWidget1_C'";
	ConstructorHelpers::FClassFinder<UUserWidget> widget(*path);
	if (widget.Succeeded())
		WidgetClass = widget.Class;

	path = L"WidgetBlueprintGeneratedClass'/Game/DynamicCombatSystem/Widgets/WB_LockIcon.WB_LockIcon_C'";
	ConstructorHelpers::FClassFinder<UUserWidget> target(*path);
	if (target.Succeeded())
		TargetWidgetClass = target.Class;

	path = L"Blueprint'/Game/MyGameProjection/Item/MyCFireball.MyCFireball_C'";
	ConstructorHelpers::FClassFinder<ACFireball> fireball(*path);
	if (fireball.Succeeded())
		FireballClass = fireball.Class;

	path = L"Blueprint'/Game/MyCAudioActor.MyCAudioActor_C'";
	ConstructorHelpers::FClassFinder<ACAudioActor> music(*path);
	if (music.Succeeded())
		audioClass = music.Class;

	ConstructorHelpers::FObjectFinder<UParticleSystem>particle
	(
		L"ParticleSystem'/Game/DynamicCombatSystem/VFX/P_Teleport.P_Teleport'"
	);
	if (particle.Succeeded())
		WarpParticle = particle.Object;

	ConstructorHelpers::FObjectFinder<UParticleSystem>mparticle
	(
		L"ParticleSystem'/Game/DynamicCombatSystem/VFX/P_Teleport.P_Teleport'"
	);
	if (mparticle.Succeeded())
		WarpParticle = mparticle.Object;

	path = L"ParticleSystem'/Game/InfinityBladeEffects/Effects/FX_Monsters/FX_Monster_Gruntling/Lightning/P_Gruntling_Lightning_Impact_03.P_Gruntling_Lightning_Impact_03'";
	ConstructorHelpers::FObjectFinder<UParticleSystem> blood(*path);
	if (blood.Succeeded())
		Blood = blood.Object;

	path = L"SoundCue'/Game/DynamicCombatSystem/SFX/CUE/Cue_HitSword.CUE_HitSword'";
	ConstructorHelpers::FObjectFinder<USoundBase> pain(*path);
	if (pain.Succeeded())
		PainSound = pain.Object;

	path = L"SoundWave'/Game/SFX/WAV/WAV_BlockMetalMetal.WAV_BlockMetalMetal'";
	ConstructorHelpers::FObjectFinder<USoundBase> block(*path);
	if (block.Succeeded())
		BlockSound = block.Object;

	path = L"AnimMontage'/Game/Enemy/Frank_RPG_Katana_Block_Montage.Frank_RPG_Katana_Block_Montage'";
	ConstructorHelpers::FObjectFinder<UAnimMontage> blocking(*path);
	if (blocking.Succeeded())
		BlockReactionMontage = blocking.Object;

	//path = L"Class'/Script/U1908_04_Combat.CAIController'";
	//ConstructorHelpers::FClassFinder<ACAIController> controller(*path);
	//if (controller.Succeeded())
	//	AIControllerClass = controller.Class;
	//AIControllerClass = AIController->GetClass();
	AIControllerClass = ACAIController::StaticClass();
	//CineCamera = CreateDefaultSubobject<UCineCameraComponent>(TEXT("CineCamera"));
	//CineCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);

	//CineCamera2 = CreateDefaultSubobject<UCineCameraComponent>(TEXT("CineCamera2"));
	//CineCamera2->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);

	//CineCamera3 = CreateDefaultSubobject<UCineCameraComponent>(TEXT("CineCamera3"));
	//CineCamera3->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);

	
	StateManager = CreateDefaultSubobject<UCCStateManager>(TEXT("CCStateManager"));
	ExtendedStamina = CreateDefaultSubobject<UCExtendedStamina>(TEXT("CExtendedStamina"));
	ExtendedHealth = CreateDefaultSubobject<UCExtendedStamina>(TEXT("ExtendedHealth"));
	RotateComponent = CreateDefaultSubobject<URotateComponent>(TEXT("CRotateComponent"));


	StateManager->SetState(E_State::Idle);
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;//**
	//StateManager->OnActivityChanged.AddDynamic(this, &ACEnemy::ChangeActivity);

	//Hp = ExtendedHealth->GetCurrentValue() / ExtendedHealth->GetMaxValue();
	StateWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("StateWidget"));
	StateWidget->SetupAttachment(GetMesh());
	StateWidget->SetWorldLocation(FVector(0,0,140));
	StateWidget->SetWidgetSpace(EWidgetSpace::Screen);
	StateWidget->SetWidgetClass(WidgetClass);
	//TargetWidget->__PPO__bIsTwoSided = true;

	//StateWidget->SetHiddenInGame(false);

	//StateWidget->

	TargetWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("TargetWidget"));
	TargetWidget->SetupAttachment(GetCapsuleComponent());
	TargetWidget->SetWidgetSpace(EWidgetSpace::Screen);
	TargetWidget->SetDrawSize(FVector2D(200, 200));
	TargetWidget->SetWidgetClass(TargetWidgetClass);
	TargetWidget->SetHiddenInGame(true);
	//TargetWidget->__PPO__bIsTwoSided = true;
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel1, ECollisionResponse::ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel1, ECollisionResponse::ECR_Block);

}

void ACEnemy::BeginPlay()
{
	Super::BeginPlay();
	SpawnPoint.X = GetActorLocation().X;
	SpawnPoint.Y = 0;
	SpawnPoint.Z = GetActorLocation().Z;

	//FString name = "AIController" + GetName().Replace(L"BpCEnemy", L"");
	//GetController()->Rename(*name);
	AIController = Cast<ACAIController>(Controller);
	//Target = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetCameraLocation());
	//CLog::Print(Target.ToString());
	//TargetWidget->SetWorldRotation(Target);


	GetController()->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepWorld, true));

	if (enemyType == E_EnemyType::Drangon)
		GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Flying);

	FTransform transform = FTransform::Identity;
	FActorSpawnParameters params;
	params.Owner = this;

	Cast<UCEnemyWidget>(StateWidget->GetUserWidgetObject())->enemy = this;
	//CLog::Print(UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetCameraLocation()).ToString());
	//CLog::Print(TEXT("BeginPlay"));

	RetNull(CameraOne)
	CameraOne->AttachToComponent(CameraBoom, FAttachmentTransformRules::KeepRelativeTransform, USpringArmComponent::SocketName);
	
	RetNull(mySummon)
	CLog::Print(TEXT("mySummonset"));
	//RetNull(WidgetClass)

	//GetMesh()->OnComponentBeginOverlap.AddDynamic(this, &ACEnemy::OnBegin);
	//GetMesh()->OnComponentEndOverlap.AddDynamic(this, &ACEnemy::OnEnd);

	

}

void ACEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//StateWidget->SetHiddenInGame(false);
	//CLog::Print(Target.ToString());
	//TargetWidget->SetWorldRotation(Target);
	//CLog::Print(TEXT("SetRotation"));

	if (IsActivityPure(E_Activity::IsBlockingPressed))
	{
		if (bCanBlock)
			Blocking = true;
		GetCharacterMovement()->MaxWalkSpeed = 200.0f;
		//CLog::Print(TEXT("true"));
	}
	else
	{
		Blocking = false;
		GetCharacterMovement()->MaxWalkSpeed = 400.0f;
		//CLog::Print(TEXT("false"));
	}
	//else if (StateManager->GetState() == E_State::Attacking)//&& enemyType == E_EnemyType::Warrok)
	//{
	//	Blocking = false;
	//	GetCharacterMovement()->MaxWalkSpeed = 30000.0f;
	//}
	//RetNull(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));


	//if (StateManager->GetState() == E_State::Dead && OnDead.IsBound())
	//{
	//	const float TimeBetweenCameraChanges = 1.0f;
	//	const float SmoothBlendTime = 0.75f;
	//	if (TimeToNextCameraChange < 0.5f)
	//	{

	//	}
	//		TimeToNextCameraChange -= DeltaTime;


	//	if (TimeToNextCameraChange <= 0.0f)
	//	{
	//		TimeToNextCameraChange += TimeBetweenCameraChanges;

	//		//Find the actor that handles control for the local player.
	//		APlayerController* OurPlayerController = UGameplayStatics::GetPlayerController(this, 0);
	//		if (OurPlayerController)
	//		{
	//			if (CameraTwo && (OurPlayerController->GetViewTarget() == CameraOne))
	//			{
	//				//Blend smoothly to camera two.
	//				OurPlayerController->SetViewTargetWithBlend(CameraTwo, SmoothBlendTime);
	//				//return;
	//			}
	//			else if (CameraOne)
	//			{
	//				//Cut instantly to camera one.
	//				OurPlayerController->SetViewTarget(CameraOne);
	//			}
	//		}
	//	}

	//}
}

void ACEnemy::TakeDamage()
{
	if (StateManager->GetState() == E_State::Dead) return;
	StateManager->SetState(E_State::Damage);



	ExtendedHealth->ModifyStat(-Damage, false);

	if (Blocking)
	{
		BlockReaction();
		Damage = Damage / 5;
		UGameplayStatics::PlaySoundAtLocation(this, BlockSound, GetActorLocation());

	}
	else
	{
		HitReaction();
		UGameplayStatics::PlaySoundAtLocation(this, PainSound, GetActorLocation());
	}



	if (ExtendedHealth->GetCurrentValue() <= 0)
	{
		Dead();
	}
	//else if (Hp <= 50)
	//{
	//	Stun();
	//	return Damage;
	//}
	//if (state == E_State::Damage) return 0;


	
	//BloodSpilt();

}

float ACEnemy::TakeDamage(float Damage, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	if (StateManager->GetState() == E_State::Dead) return 0;
	if (StateManager->GetState() == E_State::Damage) return 0;
	if (DamageCauser == this) return 0;
	


	if (Blocking)
	{
		BlockReaction();
		Damage = Damage / 2;
		UGameplayStatics::PlaySoundAtLocation(this, BlockSound, GetActorLocation(),5);

	}
	else
	{
		if (CombatType != E_CombatType::Summon && CombatType != E_CombatType::Magic)
		{
			if ((enemyType == E_EnemyType::Master || enemyType == E_EnemyType::Warrok) && (CombatType == E_CombatType::Range|| CombatType == E_CombatType::Melee))
			{
				StateManager->SetState(E_State::Damage);
				GetWorldTimerManager().SetTimer(CountdownTimerHandle, this, &ACEnemy::ResetState, 0.1f, false);
				UGameplayStatics::PlaySoundAtLocation(this, PainSound, GetActorLocation(), 3);
				ExtendedHealth->ModifyStat(-Damage, false);
				if (ExtendedHealth->GetCurrentValue() <= 0)
				{
					Dead();
					return Damage;
				}
				return Damage;
				
			}

			HitReaction();
		}
		
		UGameplayStatics::PlaySoundAtLocation(this, PainSound, GetActorLocation(),3);
	}
	if (DamageCauser->IsA(ACCombatCharacter::StaticClass()))
	{
		FVector VSocket = FVector(0, 0, 0);
		if (Cast<ACCombatCharacter>(DamageCauser)->GetWeaponType() == E_WeaponType::Sword)
		{
			VSocket = Cast<ACCombatCharacter>(DamageCauser)->GetSword()->GetWeaponMesh()->GetSocketLocation("Socket_6");
		}
		FVector VActor = GetActorLocation();
		FVector Normalize =
			VActor + UKismetMathLibrary::Normal(VSocket - VActor) * 40;
		if (IsValid(Blood))
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Blood, Normalize);

		}
	}
	if (DamageCauser->IsA(ACArrow::StaticClass()))
	{
		FVector VSocket;

		VSocket = Cast<ACArrow>(DamageCauser)->Arrow->GetSocketLocation("Socket_Hit");
		FVector VActor = GetActorLocation();
		//FVector Normalize =
		//	VActor + UKismetMathLibrary::Normal(VSocket - VActor) * 40;
		if (IsValid(Blood))
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Blood, VSocket);

		}
	}
	
	ExtendedHealth->ModifyStat(-Damage, false);

	if (ExtendedHealth->GetCurrentValue() <= 0)
	{
		Dead();
		return Damage;
	}




	//else if (Hp <= 50)
	//{
	//	Stun();
	//	return Damage;
	//}
	//CLog::Print(Damage);
	//if (state == E_State::Damage) return 0;


	//BloodSpilt();

	return Damage;
}



void ACEnemy::BeginAttack()
{
	if (StateManager->GetState() != E_State::Idle)
		return;
	StateManager->SetState(E_State::Attacking);
	if (enemyType == E_EnemyType::SwordMan)
	{
		if (!bHeavyAttack)
		{
			PlayAnimMontage(AttackMontage, 1.5f);
			ExtendedStamina->ModifyStat(-40, true);

		}
		else
		{
			PlayAnimMontage(HeavyAttackMontage, 1.5f);
			ExtendedStamina->ModifyStat(-60, true);

		}
	}
	if (enemyType == E_EnemyType::Archer)
	{
		OnAiming();
		//StateManager->SetActivity(E_Activity::IsAimingPressed, false);
		//PlayAnimMontage(RangeAttackMontage, 1.5f);
		//ExtendedStamina->ModifyStat(-40, true);
	}
	if (enemyType == E_EnemyType::Master)
	{
		if (CombatType == E_CombatType::Melee)
		{
			if (!bHeavyAttack)
			{
				PlayAnimMontage(AttackMontage, 1.5f);
				ExtendedStamina->ModifyStat(-40, true);

			}
			else
			{
				PlayAnimMontage(HeavyAttackMontage, 1.5f);
				ExtendedStamina->ModifyStat(-60, true);

			}
		}
		if (CombatType == E_CombatType::Range)
		{
			PlayAnimMontage(RangeAttackMontage, 1.5f);
			ExtendedStamina->ModifyStat(-30, true);
		}
		if (CombatType == E_CombatType::Magic)
		{
			PlayAnimMontage(MagicAttackMontage, 1.5f);
			ExtendedStamina->ModifyStat(-40, true);
		}
		if (CombatType == E_CombatType::Summon)
		{
			PlayAnimMontage(MagicSummonMontage, 1.5f);
			ExtendedStamina->ModifyStat(-40, true);
		}
	}

	if (enemyType == E_EnemyType::Warrok)
	{
		if (CombatType == E_CombatType::Melee)
		{
			//if (!bHeavyAttack)
			//{
				PlayAnimMontage(AttackMontage, 1.5f);
				ExtendedStamina->ModifyStat(-40, true);

			//}
			//else
			//{
			//	PlayAnimMontage(HeavyAttackMontage, 1.5f);
			//	ExtendedStamina->ModifyStat(-60, true);

			//}
		}
		if (CombatType == E_CombatType::Range)
		{
			PlayAnimMontage(RangeAttackMontage, 1.5f);
			ExtendedStamina->ModifyStat(-30, true);

		}
		if (CombatType == E_CombatType::Magic)
		{
			PlayAnimMontage(MagicAttackMontage, 1.5f);
			ExtendedStamina->ModifyStat(-40, true);
		}
		if (CombatType == E_CombatType::Summon)
		{
			PlayAnimMontage(MagicSummonMontage, 1.5f);
			ExtendedStamina->ModifyStat(-40, true);
		}
	}

	if (enemyType == E_EnemyType::Magy)
	{
		if (CombatType == E_CombatType::Melee)
		{
			if (!bHeavyAttack)
			{
				PlayAnimMontage(AttackMontage, 1.5f);
				ExtendedStamina->ModifyStat(-40, true);

			}
			else
			{
				PlayAnimMontage(HeavyAttackMontage, 1.5f);
				ExtendedStamina->ModifyStat(-60, true);

			}
		}
		if (CombatType == E_CombatType::Range)
		{
			PlayAnimMontage(RangeAttackMontage, 1.5f);
			ExtendedStamina->ModifyStat(-30, true);

		}
		if (CombatType == E_CombatType::Magic)
		{
			//PlayAnimMontage(MagicAttackMontage, 1.5f);
			//ExtendedStamina->ModifyStat(-40, true);
		}
		if (CombatType == E_CombatType::Summon)
		{
			PlayAnimMontage(MagicSummonMontage, 1.5f);
			ExtendedStamina->ModifyStat(-40, true);
		}
	}


	if (enemyType == E_EnemyType::Drangon)
	{
		PlayAnimMontage(RangeAttackMontage, 1.5f);
		ExtendedStamina->ModifyStat(-30, true);
	}
}

void ACEnemy::UpdateFlightTimeline(UCurveFloat * CurveFloat)
{
	Timeline = FTimeline();//Timeline초기화

	FOnTimelineFloat progress;
	//progress.BindUFunction(this, "Progress");

	Timeline.AddInterpFloat(CurveFloat, progress);
	Timeline.SetLooping(false);
	Timeline.SetTimelineLengthMode(TL_LastKeyFrame);


	FOnTimelineEvent timelineEvent;//
	//timelineEvent.BindUFunction(this, "ResetProgress");//리셋
	Timeline.SetTimelineFinishedFunc(timelineEvent);//상황에따라 이벤트 콜
}


void ACEnemy::EndAttack()
{
	StateManager->SetState(E_State::Idle);
	OnEndAttack.Broadcast();
}

//void ACEnemy::AttackCheck()
//{
//	//FHitResult HitResult;
//
//	//FCollisionQueryParams Params;
//	//Params.AddIgnoredActor(this);
//	//bool bResult = GetWorld()->SweepSingleByChannel(
//	//	HitResult,
//	//	GetActorLocation(),
//	//	GetActorLocation() + GetActorForwardVector() * 50.0f,
//	//	FQuat::Identity,
//	//	ECollisionChannel::ECC_GameTraceChannel5,
//	//	FCollisionShape::MakeSphere(50.0f),
//	//	Params);
//
//	//if (bResult)
//	//{
//	//	//UE_LOG(LogTemp, Log, TEXT("Zombie Hit: %s"), *HitResult.GetActor()->GetName());
//	//	if (HitResult.GetActor()->ActorHasTag("MyCCombatCharacter1"))
//	//	{
//	//		FDamageEvent DamageEvent;
//
//	//		HitResult.Actor->TakeDamage(20, DamageEvent, GetController(), this);
//
//	//	}
//	//}
//
//	//OnAttackHitCheck.Broadcast();
//}

void ACEnemy::HitReaction()
{
	if (StateManager->GetState() == E_State::Dead) return;
	//state = E_State::Damage;
	StateManager->SetState(E_State::Damage);
	bGetDamaged = true;
	//CLog::Print(TEXT("Hit"));
	//GetWorldTimerManager().SetTimer(CountdownTimerHandle, this, &ACEnemy::OnCollision, 0.5f, false);
	RetNull(HitReactionMontage);
	PlayAnimMontage(HitReactionMontage, 1.3f);
}

void ACEnemy::BlockReaction()
{
	if (StateManager->GetState() == E_State::Dead) return;
	//state = E_State::Damage;
	StateManager->SetState(E_State::Damage);
	RetNull(BlockReactionMontage);
	PlayAnimMontage(BlockReactionMontage, 1.3f);
}

void ACEnemy::BloodSpilt()
{
	FVector Spawnlocation = GetActorLocation();
	Spawnlocation.X -= 50;
	Spawnlocation.Y -= 50;
	Spawnlocation.Z += 50;

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Blood,
		Spawnlocation, FRotator(0, 0, 0), FVector(2, 2, 2), true, EPSCPoolMethod::None);
}

void ACEnemy::Dead()
{
	StateManager->SetState(E_State::Dead);

	OnDeadAnimtion();

	//if (StateManager->GetState() == E_State::Dead)
	//{
	//	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	//	OnEndAttack.Broadcast();
	//	OnDead.Broadcast();
	//	OurPlayerController = UGameplayStatics::GetPlayerController(this, 0);
	//	OurPlayerController->SetViewTarget(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	//	//return;
	//}
	AIController->ClearFocus(EAIFocusPriority::Gameplay);
	RotateComponent->SetRotationMode(E_RotationMode::OrientToMovement);
	GetCharacterMovement()->SetMovementMode( EMovementMode::MOVE_Falling);

	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	//UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetViewTargetWithBlend(CineCamera->GetOwner(), 0, VTBlend_Linear, 0, false);
	DeadPoint.X = GetTransform().GetLocation().X;
	DeadPoint.Y = 0;
	DeadPoint.Z = GetTransform().GetLocation().Z;
	const float SmoothBlendTime = 0.75f;



	if (bLastOne)
	{
		UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 0.3);
		GetWorldTimerManager().SetTimer(CountdownTimerHandle, this, &ACEnemy::ResetTime, 1.0f, false);
	}

	if(enemyType == E_EnemyType::Master)
	{
		UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 0.3);
		GetWorldTimerManager().SetTimer(CountdownTimerHandle, this, &ACEnemy::ResetTime, 1.0f, false);
		RetNull(audioClass);
		RetNull(audio);
		audio->FadeOut();
	}


	OurPlayerController = UGameplayStatics::GetPlayerController(this, 0);
	if (OurPlayerController)
	{
		//OurPlayerController->SetViewTarget(CameraOne);
		//OurPlayerController->SetViewTargetWithBlend(CineCamera->GetAttachmentRootActor(), SmoothBlendTime);

	}
	StateWidget->SetHiddenInGame(true);

	RetNull(mySummon);
	mySummon->IsDead();
}

void ACEnemy::Stun()
{
	StateManager->SetState(E_State::Stun);
	RetNull(StunMontage);
	PlayAnimMontage(StunMontage, 1.0);
}

void ACEnemy::ResetState()
{
	if (StateManager->GetState()== E_State::Dead)
	{
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		OnEndAttack.Broadcast();
		OnDead.Broadcast();
		OurPlayerController = UGameplayStatics::GetPlayerController(this, 0);
		OurPlayerController->SetViewTarget(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
		return;
	}
	GetCharacterMovement()->MaxWalkSpeed = 400.0f;
	StateManager->SetState(E_State::Idle);
	OnEndAttack.Broadcast();
}

bool ACEnemy::IsActivityPure(E_Activity Activity)
{
	return StateManager->GetActivityValue(Activity);

}

void ACEnemy::ResetTime()
{
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1);

}

void ACEnemy::OnAiming()
{
	
	StateManager->SetActivity(E_Activity::IsAimingPressed, true);
	UpdateFlightTimeline(CurveFloat);

	Timeline.Play();

	if (ArrowClass != NULL)
	{
		UWorld* const World = GetWorld();
		if (World != NULL)
		{
			//const FRotator SpawnRotation = GetControlRotation();
			//const FVector SpawnLocation = ArrowLocation->GetComponentLocation();// +FVector(100.0f, 0.0f, 10.0f);
			const FRotator SpawnRotation = ArrowLocation->GetComponentRotation();// GetControlRotation();
			const FVector SpawnLocation = ArrowLocation->GetComponentLocation();// +FVector(100.0f, 0.0f, 10.0f);

			//((ArrowLocation != nullptr) ? 
			//ArrowLocation->GetComponentLocation() : GetActorLocation()) + SpawnRotation.RotateVector({ 100.0f, 0.0f, 10.0f });

			FActorSpawnParameters ActorSpawnParams;
			//ActorSpawnParams.Owner = this;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
			//if (IsValid(ArrowClass))
			if (bShooted)
			{
				Arrow = World->SpawnActor<ACArrow>(ArrowClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
				Arrow->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepWorld, true), "bow_string");
				bShooted = false;
			}

		}
	}

}

void ACEnemy::OffAiming()
{

	if (enemyType == E_EnemyType::Master)
	{
		NormalShootBoom();
	}
	if (enemyType == E_EnemyType::Drangon || enemyType == E_EnemyType::Magy)
	{
		NormalShootfireball();
	}
	if (enemyType == E_EnemyType::Archer)
	{
		RetNull(Arrow);
		FVector vector;
		Arrow->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		Arrow->SetActorRotation(GetControlRotation());
		Arrow->OnShoot(FQuat(GetControlRotation()).GetForwardVector());
	}


}

void ACEnemy::SetCombatType(E_CombatType SCombatType)
{
	CombatType = SCombatType;
}

//void ACEnemy::OnBegin(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
//{
//	CLog::Print(TEXT("OnBegin"));
//	RetNull(OtherActor);
//	RetNull(OtherComp);
//	if (OtherActor == this)return;
//
//	if (OtherActor->GetClass()->IsChildOf(ACHuricain::StaticClass()))
//	{
//		CLog::Print(TEXT("OnBegin"));
//		Huricain = Cast<ACHuricain>(OtherActor);
//		GetWorldTimerManager().SetTimer(HuricainTimerHandle, this, &ACEnemy::TakeDamage, 1.0f, false);
//
//	}
//
//}
//
//void ACEnemy::OnEnd(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
//{
//	RetNull(OtherActor);
//	RetNull(OtherComp);
//	if (OtherActor == this)return;
//
//	if (Huricain != NULL)
//		Huricain = NULL;
//	GetWorldTimerManager().ClearTimer(HuricainTimerHandle);
//
//}

void ACEnemy::OnDeadAnimtion()
{
	RetNull(DeadMontage);
	PlayAnimMontage(DeadMontage, 1.0);

}

void ACEnemy::MagicBoom()
{
	//ShootBoom();
	GetWorldTimerManager().SetTimer(CountdownTimerHandle, this, &ACEnemy::ShootBoom, 0.45f, true);
	GetWorldTimerManager().SetTimer(CountdownTimerHandle, this, &ACEnemy::Fallingboom, 1.0f, false);

}

void ACEnemy::NormalShootBoom()
{
	if (NormalBoomClass != NULL)
	{
		UWorld* const World = GetWorld();
		if (World != NULL)
		{
			
			const FRotator SpawnRotation = GetControlRotation();

			FVector SpawnLocation = ArrowLocation->GetComponentLocation();// +FVector(100.0f, 0.0f, 10.0f);
			//((ArrowLocation != nullptr) ? 
			//ArrowLocation->GetComponentLocation() : GetActorLocation()) + SpawnRotation.RotateVector({ 100.0f, 0.0f, 10.0f });
			//SpawnLocation.Z = 500;
			FActorSpawnParameters ActorSpawnParams;
			//ActorSpawnParams.Owner = this;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
			//if (IsValid(ArrowClass))
			World->SpawnActor<ACBoom>(NormalBoomClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
			
		}
		//Arrow->Draw();

		//Arrow.AddUnique(Arrow);
		//Arrow->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), "bow_string");

	}
}

void ACEnemy::ShootBoom()
{
	if (ShootBoomClass != NULL)
	{
		UWorld* const World = GetWorld();
		if (World != NULL)
		{
			const FRotator SpawnRotation = GetControlRotation();
			FVector SpawnLocation = ArrowShootLocation->GetComponentLocation();// +FVector(100.0f, 0.0f, 10.0f);
			//((ArrowLocation != nullptr) ? 
			//ArrowLocation->GetComponentLocation() : GetActorLocation()) + SpawnRotation.RotateVector({ 100.0f, 0.0f, 10.0f });
			//SpawnLocation.Z = 500;
			FActorSpawnParameters ActorSpawnParams;
			//ActorSpawnParams.Owner = this;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
			//if (IsValid(ArrowClass))
			World->SpawnActor<ACBoom>(ShootBoomClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
		}
		//Arrow->Draw();

		//Arrow.AddUnique(Arrow);
		//Arrow->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), "bow_string");

	}
}

void ACEnemy::Fallingboom()
{
	GetWorldTimerManager().ClearTimer(CountdownTimerHandle);

	if (BoomClass != NULL)
	{
		UWorld* const World = GetWorld();
		if (World != NULL)
		{
			const FRotator SpawnRotation = GetControlRotation();
			//FVector SpawnLocation = UKismetMathLibrary::RandomPointInBoundingBox(GetActorLocation(), FVector(500, 500, 0));// +FVector(100.0f, 0.0f, 10.0f);
			//((ArrowLocation != nullptr) ? 
			//ArrowLocation->GetComponentLocation() : GetActorLocation()) + SpawnRotation.RotateVector({ 100.0f, 0.0f, 10.0f });
			
			FActorSpawnParameters ActorSpawnParams;
			//ActorSpawnParams.Owner = this;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
			//if (IsValid(ArrowClass))
			for (int i = 0; i < 5; i++)
			{
				FVector SpawnLocation = UKismetMathLibrary::RandomPointInBoundingBox(GetActorLocation(), FVector(500, 500, 0));// +FVector(100.0f, 0.0f, 10.0f);
				SpawnLocation.Z = GetActorLocation().Z + 2000;
				World->SpawnActor<ACBoom>(BoomClass, SpawnLocation, SpawnRotation, ActorSpawnParams);

			}
		}
		//Arrow->Draw();

		//Arrow.AddUnique(Arrow);
		//Arrow->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), "bow_string");

	}


}

void ACEnemy::SummonEnemy()
{

	if (SpawnClass != NULL)//	if (SummonClass != NULL)
	{
		UWorld* const World = GetWorld();
		if (World != NULL)
		{
			const FRotator SpawnRotation = GetActorRotation();
				//GetControlRotation();
			//FVector SpawnLocation = UKismetMathLibrary::RandomPointInBoundingBox(GetActorLocation(), FVector(500, 500, 0));// +FVector(100.0f, 0.0f, 10.0f);
			//((ArrowLocation != nullptr) ? 
			//ArrowLocation->GetComponentLocation() : GetActorLocation()) + SpawnRotation.RotateVector({ 100.0f, 0.0f, 10.0f });

			FActorSpawnParameters ActorSpawnParams;
			//ActorSpawnParams.Owner = this;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
			//if (IsValid(ArrowClass))
			for (int i = 0; i < 3; i++)
			{
				FVector SpawnLocation = UKismetMathLibrary::RandomPointInBoundingBox(GetActorLocation(), FVector(500, 500, 0));// +FVector(100.0f, 0.0f, 10.0f);
				SpawnLocation.Z = GetActorLocation().Z - Summonpoint;
				//World->SpawnActor<ACEnemy>(SummonClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
				World->SpawnActor<ACSpawn>(SpawnClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
			}
		}
		//Arrow->Draw();

		//Arrow.AddUnique(Arrow);
		//Arrow->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), "bow_string");
		SpawnedEnemyCount++;
	}


}


FRotator ACEnemy::GetDesireRotation()
{
	FRotator MakeRotator = GetActorRotation();

	if (IsValid(AIController))
	{
		//if (IsValid(AIController->GetTarget))
		//{
		//	
		//}
		MakeRotator.Yaw = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), AIController->GetTarget->GetActorLocation()).Yaw;
		return MakeRotator;
	}
	else
		return FRotator(0, 0, 0);
}

bool ACEnemy::OnDeselected()
{
	if (IsValid(TargetWidget))
	{
		TargetWidget->SetHiddenInGame(true, false);
	}
	return false;
}

bool ACEnemy::OnSelected()
{
	if (IsValid(TargetWidget))
	{
		//Target = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetCameraLocation());
		//TargetWidget->SetWorldRotation(Target);
		TargetWidget->SetHiddenInGame(false, false);
	}
	return false;
}

bool ACEnemy::IsTargetable()
{
	if(StateManager->GetState()==E_State::Dead)
		return false;
	else
		return true;
}

void ACEnemy::NormalShootfireball()
{
	if (FireballClass != NULL)
	{
		UWorld* const World = GetWorld();
		if (World != NULL)
		{
			const FRotator SpawnRotation = GetControlRotation();
			//const FVector SpawnLocation = ShootRightLocation->GetComponentLocation();// +FVector(100.0f, 0.0f, 10.0f);

			const FVector SpawnLocation = ArrowShootLocation->GetComponentLocation();// +FVector(100.0f, 0.0f, 10.0f);
			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
			RetNull(FireballClass);
			World->SpawnActor<ACFireball>(FireballClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
		}
	}
}

void ACEnemy::OnJumping()
{
	FVector start = GetActorLocation();
	FVector end = GetActorLocation();

	start.Z -= 150.0f;
	end.Z += 100.0f;

	FCollisionShape sphere = FCollisionShape::MakeSphere(200.0f);
	//DrawDebugSphere(GetWorld(), GetActorLocation(), sphere.GetSphereRadius(), 40, FColor::Green, true);
	//DrawDebugSphere(GetWorld(), start, sphere.GetSphereRadius(), 40, FColor::Green, false, 1);
	TArray<FHitResult>hits;


	bool bHit = GetWorld()->SweepMultiByChannel(hits, start, end, FQuat::Identity, ECC_WorldDynamic, sphere);
	TArray<AActor*>me;
	me.Add(this);

	if (bHit)
	{
		for (auto& hit : hits)
		{
			USkeletalMeshComponent* mesh = Cast<USkeletalMeshComponent>(hit.GetActor()->GetRootComponent());
			bool b = true;
			//b &= mesh != NULL;
			//if (GetOwner()->IsA(ACParty::StaticClass()))
			//	b &= hit.GetActor()->IsA(ACParty::StaticClass()) == false;
			//if (GetOwner()->IsA(ACEnemy::StaticClass()))
			//	b &= hit.GetActor()->IsA(ACEnemy::StaticClass()) == false;
			if (hit.GetActor() == this)
				b &= hit.GetActor()->IsA(ACEnemy::StaticClass()) == false;
			//b &= hit.GetActor()->IsA(ACParty::StaticClass()) == true;
			//b &= hit.GetActor()->GetName().Contains("Wall") == false;
			//b &= hit.GetActor()->GetName().Contains("FirstPersonCharacter") == false;

			if (b)
			{


				//ACEnemy* enemy = Cast<ACEnemy>(hit.GetActor());
				//float damage = 1;
				//if (enemy->GetEnemyType() == E_EnemyType::Master)
				//	damage = 15;
				//UDamageType ud;
				UGameplayStatics::ApplyDamage(hit.GetActor(), 10.0f * 2, NULL, this, NULL);
				//UGameplayStatics::ApplyRadialDamage(GetWorld(), damage, GetActorLocation(),0,NULL,NULL,this);
				//if (hit.GetActor()->IsA(ACEnemy::StaticClass()))
				//{
				//	UGameplayStatics::ApplyRadialDamage(GetWorld(), 15, GetActorLocation(), 200.0f, NULL, me, this, NULL, true, ECC_Visibility);

				//}
			}
			//mesh->AddRadialImpulse(GetActorLocation(), Radius, mesh->GetMass()*1.25f, ERadialImpulseFalloff::RIF_Constant, true);//발산
		//force 충돌
		}
	}
	//Particle->Activate(true);
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DSword->Particle, start, GetActorRotation());
	UGameplayStatics::PlaySoundAtLocation(this, DSword->BoomSound, start);
	bHit = false;
	//FlushPersistentDebugLines(GetWorld());
	//Destroy();
}

void ACEnemy::OnWarp(FVector warpPoint)
{
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), WarpParticle, GetActorLocation(), FRotator());
	SetActorLocation(warpPoint);
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), WarpParticle, warpPoint, FRotator());
	//UGameplayStatics::PlaySoundAtLocation(this, DSword->BoomSound, warpPoint);

}

void ACEnemy::OnSpellIndicator(FVector MagicPoint)
{

	SpellLocation = UGameplayStatics::GetPlayerPawn(this,0)->GetActorLocation();
	//CLog::Print(SpellLocation.ToString());

	if (IsValid(MagicAttackMontage))
		PlayAnimMontage(MagicAttackMontage, 1.5f);
	ExtendedStamina->ModifyStat(-40, true);


	if (MagicClass != NULL)
	{
		UWorld* const World = GetWorld();
		if (World != NULL)
		{
			//const FRotator SpawnRotation = GetControlRotation();
			//const FVector SpawnLocation = ArrowLocation->GetComponentLocation();// +FVector(100.0f, 0.0f, 10.0f);
			const FRotator SpawnRotation = FRotator(0,0,0);// GetControlRotation();
			const FVector SpawnLocation = MagicPoint;// +FVector(100.0f, 0.0f, 10.0f);
			
			//((ArrowLocation != nullptr) ? 
			//ArrowLocation->GetComponentLocation() : GetActorLocation()) + SpawnRotation.RotateVector({ 100.0f, 0.0f, 10.0f });

			FActorSpawnParameters ActorSpawnParams;
			//ActorSpawnParams.Owner = this;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
			if (IsValid(MagicClass))
			{
				SpellIndicator = World->SpawnActor<ACSpellIndicator>(MagicClass, SpellLocation, FRotator(), ActorSpawnParams);
				//GetWorldTimerManager().SetTimer(MagicTimerHandle, this, &ACEnemy::ResetState, 0.1f, false);

			}

		}
	}


	//UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), MagicParticle, MagicPoint, FRotator());
}

void ACEnemy::OnMagic()
{
	RetNull(MagicParticle)
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), MagicParticle, SpellLocation, FRotator(0,-90,0));
	//UGameplayStatics::PlaySoundAtLocation(this, BoomSound, SpellLocation);

	FVector start = SpellLocation;
	FVector end = SpellLocation;

	end.Z += 100.0f;

	FCollisionShape sphere = FCollisionShape::MakeSphere(200.0f);
	//DrawDebugSphere(GetWorld(), GetActorLocation(), sphere.GetSphereRadius(), 40, FColor::Green, true);
	//DrawDebugSphere(GetWorld(), start, sphere.GetSphereRadius(), 40, FColor::Green, false, 1);
	TArray<FHitResult>hits;


	bool bHit = GetWorld()->SweepMultiByChannel(hits, start, end, FQuat::Identity, ECC_WorldDynamic, sphere);
	TArray<AActor*>me;
	me.Add(this);

	if (bHit)
	{
		for (auto& hit : hits)
		{
			USkeletalMeshComponent* mesh = Cast<USkeletalMeshComponent>(hit.GetActor()->GetRootComponent());
			bool b = true;
			//b &= mesh != NULL;
			//if (GetOwner()->IsA(ACParty::StaticClass()))
			//	b &= hit.GetActor()->IsA(ACParty::StaticClass()) == false;
			//if (this->IsA(ACEnemy::StaticClass()))
				b &= hit.GetActor()->IsA(ACEnemy::StaticClass()) == false;
			//b &= hit.GetActor()->IsA(ACEnemy::StaticClass()) == true;
			//b &= hit.GetActor()->GetName().Contains("Wall") == false;
			//b &= hit.GetActor()->GetName().Contains("FirstPersonCharacter") == false;

			if (b)
			{


				ACEnemy* enemy = Cast<ACEnemy>(hit.GetActor());
				float damage = 1;
				if (enemy->GetEnemyType() == E_EnemyType::Master)
					damage = 15;
				//UDamageType ud;
				UGameplayStatics::ApplyDamage(hit.GetActor(), 30 * 2, NULL, this, NULL);
				//UGameplayStatics::ApplyRadialDamage(GetWorld(), damage, GetActorLocation(),0,NULL,NULL,this);
				//if (hit.GetActor()->IsA(ACEnemy::StaticClass()))
				//{
				//	UGameplayStatics::ApplyRadialDamage(GetWorld(), 15, GetActorLocation(), 200.0f, NULL, me, this, NULL, true, ECC_Visibility);

				//}
			}
			//mesh->AddRadialImpulse(GetActorLocation(), Radius, mesh->GetMass()*1.25f, ERadialImpulseFalloff::RIF_Constant, true);//발산
		//force 충돌
		}
	}
	//Particle->Activate(true);	
	bHit = false;

	RetNull(MagicClass)
		SpellIndicator->Destroy();
}

void ACEnemy::OnHeal()
{

}

void ACEnemy::SetMySummon(ACSpawn * Summon)
{
	mySummon = Summon;
	//CLog::Print(TEXT("SetMySummon"));
}


