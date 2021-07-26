#include "CCombatCharacter.h"
#include "Global.h"
//#include "MyGameProject/Item/CGreateSword.h"
#include "MyGameProject/Item/CDisplayedItem.h"
#include "MyGameProject/Item/CArrow.h"
#include "MyGameProject/Item/CFireball.h"
//#include "Curves/CurveFloat.h"
#include"GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Perception/AIPerceptionSystem.h"
#include "Perception/AISense_Sight.h"
#include "CCStateManager.h"
#include "CExtendedStamina.h"
#include "TargetComponent.h"
#include "MyGameProject/PlayerWidget.h"
#include "MyGameProject/WidgetCrosshair.h"
#include "Components/SceneComponent.h"
#include "CameraChangeTrigger.h"
#include "CCameraActor.h"
#include "CHuricain.h"
#include "CEnemy.h"
#include "CBoom.h"
#include "CRope.h"
#include "CFallRespawn.h"

ACCombatCharacter::ACCombatCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	//bUseControllerRotationYaw = true;

	//GetCharacterMovement()->bOrientRotationToMovement = false;
	GetCharacterMovement()->MaxWalkSpeed = 400.0f;

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel1, ECollisionResponse::ECR_Ignore);

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->bUsePawnControlRotation = false;
	CameraBoom->SetupAttachment(GetMesh());

	CameraBoomSide = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoomSide"));
	CameraBoomSide->bUsePawnControlRotation = false;
	CameraBoomSide->SetupAttachment(GetMesh());

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);

	StateManager = CreateDefaultSubobject<UCCStateManager>(TEXT("StateManager"));
	ExtendedStamina = CreateDefaultSubobject<UCExtendedStamina>(TEXT("ExtendedStamina"));
	ExtendedHealth = CreateDefaultSubobject<UCExtendedStamina>(TEXT("ExtendedHealth"));
	DynamicTargeting = CreateDefaultSubobject<UTargetComponent>(TEXT("DynamicTargeting"));
	TargetingArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("TargetingArrow"));
	//FString path = L"Blueprint'/Game/MyGameProjection/MyCDI_Hand.MyCDI_Hand_C'";
	//ConstructorHelpers::FClassFinder<ACDisplayedItem> item(*path);
	//if (item.Succeeded())
	//	ItemClasses[0] = item.Class;
	FString path;
	//Item
	{
		//path = L"Blueprint'/Game/MyGameProjection/MyCGreateSword.MyCGreateSword_C'";
		//ConstructorHelpers::FClassFinder<ACGreateSword> sword(*path);
		//if (sword.Succeeded())
		//	SwordClass = sword.Class;

		path = L"Blueprint'/Game/MyGameProjection/MyCDI_Shield.MyCDI_Shield_C'";
		ConstructorHelpers::FClassFinder<ACDisplayedItem> shield(*path);
		if (shield.Succeeded())
			ShieldClass = shield.Class;
	}


	//Attack
	{
		path = L"AnimMontage'/Game/MyPortpol/Animation/PlayerAnimation/1HandSwordAndShield/Frank_RPG_Warrior_Combo01_1_Montage.Frank_RPG_Warrior_Combo01_1_Montage'";
		ConstructorHelpers::FObjectFinder<UAnimMontage> attack(*path);
		if (attack.Succeeded())
			AttackMontage = attack.Object;

		path = L"AnimMontage'/Game/MyPortpol/Animation/PlayerAnimation/1HandSwordAndShield/Frank_RPG_Warrior_Combo01_2_Montage.Frank_RPG_Warrior_Combo01_2_Montage'";
		ConstructorHelpers::FObjectFinder<UAnimMontage> combo1(*path);
		if (combo1.Succeeded())
			AttackComboMontage1 = combo1.Object;

		path = L"AnimMontage'/Game/MyPortpol/Animation/PlayerAnimation/1HandSwordAndShield/Frank_RPG_Warrior_Combo01_3_Montage.Frank_RPG_Warrior_Combo01_3_Montage'";
		ConstructorHelpers::FObjectFinder<UAnimMontage> combo2(*path);
		if (combo2.Succeeded())
			AttackComboMontage2 = combo2.Object;

		path = L"AnimMontage'/Game/MyPortpol/Animation/PlayerAnimation/1HandSwordAndShield/Frank_RPG_Warrior_Combo01_3_Montage.Frank_RPG_Warrior_Combo01_3_Montage'";
		ConstructorHelpers::FObjectFinder<UAnimMontage> combo3(*path);
		if (combo3.Succeeded())
			AttackComboMontage3 = combo3.Object;

		path = L"AnimMontage'/Game/MyPortpol/Animation/PlayerAnimation/1HandSwordAndShield/Frank_RPG_Warrior_Combo01_4_Montage.Frank_RPG_Warrior_Combo01_4_Montage'";
		ConstructorHelpers::FObjectFinder<UAnimMontage> combo4(*path);
		if (combo4.Succeeded())
			AttackComboMontage4 = combo4.Object;

		path = L"AnimMontage'/Game/MyPortpol/Animation/PlayerAnimation/AR_ShootAndDraw_Montage.AR_ShootAndDraw_Montage'";
		ConstructorHelpers::FObjectFinder<UAnimMontage> shoot(*path);
		if (shoot.Succeeded())
			ShoothMontage = shoot.Object;
	}

	//Parry
	{

		path = L"AnimMontage'/Game/MyPortpol/Animation/PlayerAnimation/1HandSwordAndShield/Frank_RPG_Warrior_ShieldAttack02_IP_Montage.Frank_RPG_Warrior_ShieldAttack02_IP_Montage'";
		ConstructorHelpers::FObjectFinder<UAnimMontage> parry1(*path);
		if (parry1.Succeeded())
			ParryAttackMontage1 = parry1.Object;

		//path = L"AnimMontage'/Game/MyPortpol/Animation/PlayerAnimation/1HandSwordAndShield/Frank_RPG_Warrior_Combo01_3_Montage.Frank_RPG_Warrior_Combo01_3_Montage'";
		//ConstructorHelpers::FObjectFinder<UAnimMontage> parry2(*path);
		//if (parry2.Succeeded())
		//	ParryAttackMontage2 = parry2.Object;
	}
	//Motion
	{
		path = L"AnimMontage'/Game/MyPortpol/Animation/PlayerAnimation/1HandSwordAndShield/Frank_RPG_Warrior_Evade_F_Montage.Frank_RPG_Warrior_Evade_F_Montage'";
		ConstructorHelpers::FObjectFinder<UAnimMontage> roll(*path);
		if (roll.Succeeded())
			Roll_F_Montage = roll.Object;

		path = L"AnimMontage'/Game/MyPortpol/Animation/PlayerAnimation/1HandSwordAndShield/Frank_RPG_Warrior_Evade_B_Montage.Frank_RPG_Warrior_Evade_B_Montage'";
		ConstructorHelpers::FObjectFinder<UAnimMontage> roll1(*path);
		if (roll1.Succeeded())
			Roll_B_Montage = roll1.Object;

		path = L"AnimMontage'/Game/MyPortpol/Animation/PlayerAnimation/1HandSwordAndShield/Frank_RPG_Warrior_Evade_R_Montage.Frank_RPG_Warrior_Evade_R_Montage'";
		ConstructorHelpers::FObjectFinder<UAnimMontage> roll2(*path);
		if (roll2.Succeeded())
			Roll_R_Montage = roll2.Object;

		path = L"AnimMontage'/Game/MyPortpol/Animation/PlayerAnimation/1HandSwordAndShield/Frank_RPG_Warrior_Evade_L_Montage.Frank_RPG_Warrior_Evade_L_Montage'";
		ConstructorHelpers::FObjectFinder<UAnimMontage> roll3(*path);
		if (roll3.Succeeded())
			Roll_L_Montage = roll3.Object;

		path = L"AnimMontage'/Game/MyPortpol/Animation/PlayerAnimation/Frank_RPG_Warrior_Step_F_Montage.Frank_RPG_Warrior_Step_F_Montage'";
		ConstructorHelpers::FObjectFinder<UAnimMontage> dash(*path);
		if (dash.Succeeded())
			Dash_F_Montage = dash.Object;

		path = L"AnimMontage'/Game/MyPortpol/Animation/PlayerAnimation/Frank_RPG_Warrior_Step_B_Montage.Frank_RPG_Warrior_Step_B_Montage'";
		ConstructorHelpers::FObjectFinder<UAnimMontage> dash1(*path);
		if (dash1.Succeeded())
			Dash_B_Montage = dash1.Object;

		path = L"AnimMontage'/Game/MyPortpol/Animation/PlayerAnimation/Frank_RPG_Warrior_Step_R_Montage.Frank_RPG_Warrior_Step_R_Montage'";
		ConstructorHelpers::FObjectFinder<UAnimMontage> dash2(*path);
		if (dash2.Succeeded())
			Dash_R_Montage = dash2.Object;

		path = L"AnimMontage'/Game/MyPortpol/Animation/PlayerAnimation/Frank_RPG_Warrior_Step_L_Montage.Frank_RPG_Warrior_Step_L_Montage'";
		ConstructorHelpers::FObjectFinder<UAnimMontage> dash3(*path);
		if (dash3.Succeeded())
			Dash_L_Montage = dash3.Object;
		//path = L"AnimMontage'/Game/MyGameProjection/Animation/Roll_Montage.Roll_Montage'";
		//ConstructorHelpers::FObjectFinder<UAnimMontage> hit(*path);
		//if (hit.Succeeded())
		//	HitReractionMontage = hit.Object;

	}

	//Block
	{
		path = L"AnimMontage'/Game/MyGameProjection/Animation/playeranimation/SwordAndShild/sword_and_shield_block_Montage.sword_and_shield_block_Montage'";
		ConstructorHelpers::FObjectFinder<UAnimMontage> hs(*path);
		if (hs.Succeeded())
			HS_BlockMontage = hs.Object;

		path = L"AnimMontage'/Game/MyGameProjection/Animation/playeranimation/SwordAndShild/sword_and_shield_block__2__Montage.sword_and_shield_block__2__Montage'";
		ConstructorHelpers::FObjectFinder<UAnimMontage> hsoff(*path);
		if (hsoff.Succeeded())
			HS_BlockoffMontage = hsoff.Object;

		path = L"AnimMontage'/Game/MyGameProjection/Animation/1H_Block_Montage.1H_Block_Montage'";
		ConstructorHelpers::FObjectFinder<UAnimMontage> h(*path);
		if (h.Succeeded())
			H_BlockMontage = h.Object;

		path = L"AnimMontage'/Game/MyGameProjection/Animation/MGS_Blocking_Montage.MGS_Blocking_Montage'";
		ConstructorHelpers::FObjectFinder<UAnimMontage> ms(*path);
		if (ms.Succeeded())
			MS_BlockMontage = ms.Object;

		path = L"AnimMontage'/Game/MyGameProjection/Animation/MG_Blocking_Montage.MG_Blocking_Montage'";
		ConstructorHelpers::FObjectFinder<UAnimMontage> m(*path);
		if (m.Succeeded())
			M_BlockMontage = m.Object;

	}




	//Equip/Sheath
	{
		path = L"AnimMontage'/Game/MyPortpol/Animation/PlayerAnimation/1H_DrawSword_Montage.1H_DrawSword_Montage'";
		ConstructorHelpers::FObjectFinder<UAnimMontage> equipsword(*path);
		if (equipsword.Succeeded())
			EquipSwordMontage = equipsword.Object;

		path = L"AnimMontage'/Game/MyPortpol/Animation/PlayerAnimation/1H_DisarmSword_Montage.1H_DisarmSword_Montage'";
		ConstructorHelpers::FObjectFinder<UAnimMontage> sheathsword(*path);
		if (sheathsword.Succeeded())
			SheathSwordMontage = sheathsword.Object;

		path = L"AnimMontage'/Game/MyPortpol/Animation/PlayerAnimation/AR_DrawBow_Montage.AR_DrawBow_Montage'";
		ConstructorHelpers::FObjectFinder<UAnimMontage> equipbow(*path);
		if (equipbow.Succeeded())
			EquipBowMontage = equipbow.Object;

		path = L"AnimMontage'/Game/MyPortpol/Animation/PlayerAnimation/Ar_DisarmBow_Montage.Ar_DisarmBow_Montage'";
		ConstructorHelpers::FObjectFinder<UAnimMontage> sheathbow(*path);
		if (sheathbow.Succeeded())
			SheathBowMontage = sheathbow.Object;

		path = L"AnimMontage'/Game/MyPortpol/Animation/PlayerAnimation/Magic/MG_DrawSpell_Montage.MG_DrawSpell_Montage'";
		ConstructorHelpers::FObjectFinder<UAnimMontage> equipSpell(*path);
		if (equipSpell.Succeeded())
			EquipSpellMontage = equipSpell.Object;

		path = L"AnimMontage'/Game/MyPortpol/Animation/PlayerAnimation/Magic/MG_SheathSpell_Montage.MG_SheathSpell_Montage'";
		ConstructorHelpers::FObjectFinder<UAnimMontage> sheathSpell(*path);
		if (sheathSpell.Succeeded())
			SheathSpellMontage = sheathSpell.Object;

	}

	//Magic
	{
		path = L"AnimMontage'/Game/MyPortpol/Animation/PlayerAnimation/Magic/MG_Fireball_01_Montage.MG_Fireball_01_Montage'";
		ConstructorHelpers::FObjectFinder<UAnimMontage> fireball1(*path);
		if (fireball1.Succeeded())
			FireballMontage = fireball1.Object;

		path = L"AnimMontage'/Game/MyPortpol/Animation/PlayerAnimation/Magic/MG_Fireball_02_Montage.MG_Fireball_02_Montage'";
		ConstructorHelpers::FObjectFinder<UAnimMontage> fireball2(*path);
		if (fireball2.Succeeded())
			FireballMontage2 = fireball2.Object;

		path = L"AnimMontage'/Game/MyPortpol/Animation/PlayerAnimation/Magic/MG_Fireball_03_Montage.MG_Fireball_03_Montage'";
		ConstructorHelpers::FObjectFinder<UAnimMontage> fireball3(*path);
		if (fireball3.Succeeded())
			FireballMontage3 = fireball3.Object;


	}

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


	//WindBladeLocation
	{
		//path = L"Blueprint'/Game/MyPortpol/Praticle/MyCWindBlade.MyCWindBlade_C'";
		//ConstructorHelpers::FClassFinder<ACWindBlade> windBlade(*path);
		//if (windBlade.Succeeded())
		//	WindBladeClass = windBlade.Class;

		//path = L"Blueprint'/Game/MyPortpol/Praticle/MyCWindBlade.MyCWindBlade_C'";
		//ConstructorHelpers::FClassFinder<ACFireStorm> fireStorm(*path);
		//if (fireStorm.Succeeded())
		//	FireStormClass = fireStorm.Class;

		WindBladeLocation = CreateDefaultSubobject<USceneComponent>(TEXT("WindBladeLocation"));
		WindBladeLocation->SetupAttachment(GetMesh(), L"sword_use");


	}

	//FireballLocation
	{
		path = L"Blueprint'/Game/MyGameProjection/Item/MyCFireball.MyCFireball_C'";
		ConstructorHelpers::FClassFinder<ACFireball> fireball(*path);
		if (fireball.Succeeded())
			FireballClass = fireball.Class;

		ShootRightLocation = CreateDefaultSubobject<USceneComponent>(TEXT("ShootRightLocation"));
		ShootRightLocation->SetupAttachment(GetMesh(), L"magic_right_hand");

		ShootLeftLocation = CreateDefaultSubobject<USceneComponent>(TEXT("ShootLeftLocation"));
		ShootLeftLocation->SetupAttachment(GetMesh(), L"magic_left_hand");


	}

	//Huricain
	{
		path = L"Blueprint'/Game/BpCHuricain.BpCHuricain_C'";
		ConstructorHelpers::FClassFinder<ACHuricain> huricain(*path);
		if (huricain.Succeeded())
			HuricainClass = huricain.Class;

	}

	//Widget
	{
		path = L"WidgetBlueprint'/Game/MyPortpol/Player/BPCPlayerWidget.BPCPlayerWidget_C'";
		ConstructorHelpers::FClassFinder<UUserWidget> widget(*path);
		if (widget.Succeeded())
			PlayerWidgetClass = widget.Class;

	}

	//StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");

	//FString path = L"Blueprint'/Game/Events/MyC17_Spline.MyC17_Spline_C'";//블프를 연결하려면 뒤에 _C를 붙인다.
	//ConstructorHelpers::FClassFinder<ACBlockAlpha> spline(*path);
	//if (spline.Succeeded())
	//	SplineClass = spline.Class;




	path = L"CurveFloat'/Game/MyGameProjection/Alpha/BlockAlpha.BlockAlpha'";
	ConstructorHelpers::FObjectFinder<UCurveFloat> curve(*path);
	if (curve.Succeeded())
		CurveFloat = curve.Object;

	StateManager->SetState(E_State::Idle);
	combatType = E_CombatType::Unarmed;
	magicType = E_MagicType::Fireball;
	SwordAttachPoint = "sword";
	BowAttachPoint = "bow";
	ShieldAttachPoint = "shield";
	SpellAttachPoint = "magic_right_hand";
	AttackCount = 0;
	bShieldEquipped = false;
	bBlock = false;
}

void ACCombatCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &ACCombatCharacter::OnMoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACCombatCharacter::OnMoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &ACCombatCharacter::OnTurn);
	PlayerInputComponent->BindAxis("LookUp", this, &ACCombatCharacter::OnLookUp);
	PlayerInputComponent->BindAxis("Zoom", this, &ACCombatCharacter::OnZoom);

	//PlayerInputComponent->BindAxis("GoRight", this, &ACCombatCharacter::GoRight);
	//PlayerInputComponent->BindAxis("GoLeft", this, &ACCombatCharacter::GoLeft);
	//PlayerInputComponent->BindAxis("GoUp",this, &ACCombatCharacter::GoUp);
	//PlayerInputComponent->BindAxis("GoDown", this, &ACCombatCharacter::GoDown);

	PlayerInputComponent->BindAction("WeaponChangeUp", EInputEvent::IE_Pressed, this, &ACCombatCharacter::WeaponChangeUp);
	PlayerInputComponent->BindAction("WeaponChangeDown", EInputEvent::IE_Pressed, this, &ACCombatCharacter::WeaponChangeDown);

	PlayerInputComponent->BindAction("Running", EInputEvent::IE_Pressed, this, &ACCombatCharacter::OnRunning);
	PlayerInputComponent->BindAction("Running", EInputEvent::IE_Released, this, &ACCombatCharacter::OffRunning);

	PlayerInputComponent->BindAction("Jumping", EInputEvent::IE_Pressed, this, &ACCombatCharacter::OnJumping);
	PlayerInputComponent->BindAction("Jumping", EInputEvent::IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction("Sword", EInputEvent::IE_Pressed, this, &ACCombatCharacter::OnEquip);
	PlayerInputComponent->BindAction("Attacking", EInputEvent::IE_Pressed, this, &ACCombatCharacter::OnAttacking);
	PlayerInputComponent->BindAction("Attacking", EInputEvent::IE_Released, this, &ACCombatCharacter::OffAttacking);
	
	PlayerInputComponent->BindAction("Charge", EInputEvent::IE_Pressed, this, &ACCombatCharacter::OnCharge);

	PlayerInputComponent->BindAction("Rolling", EInputEvent::IE_Pressed, this, &ACCombatCharacter::OnRolling);

	PlayerInputComponent->BindAction("Blocking", EInputEvent::IE_Pressed, this, &ACCombatCharacter::OnBlocking);
	PlayerInputComponent->BindAction("Blocking", EInputEvent::IE_Released, this, &ACCombatCharacter::OffBlocking);

	PlayerInputComponent->BindAction("Flying", EInputEvent::IE_Pressed, this, &ACCombatCharacter::OnFlying);
	PlayerInputComponent->BindAction("Flying", EInputEvent::IE_Released, this, &ACCombatCharacter::OffFlying);


	PlayerInputComponent->BindAction("MagicNum1", EInputEvent::IE_Pressed, this, &ACCombatCharacter::OnMagicNum1);
	PlayerInputComponent->BindAction("MagicNum2", EInputEvent::IE_Pressed, this, &ACCombatCharacter::OnMagicNum2);
	PlayerInputComponent->BindAction("MagicNum3", EInputEvent::IE_Pressed, this, &ACCombatCharacter::OnMagicNum3);
	PlayerInputComponent->BindAction("MagicNum4", EInputEvent::IE_Pressed, this, &ACCombatCharacter::OnMagicNum4);
	PlayerInputComponent->BindAction("MagicNum5", EInputEvent::IE_Pressed, this, &ACCombatCharacter::OnMagicNum5);
	PlayerInputComponent->BindAction("Magic", EInputEvent::IE_Pressed, this, &ACCombatCharacter::OnHuricain);
	PlayerInputComponent->BindAction("Magic", EInputEvent::IE_Released, this, &ACCombatCharacter::OffHuricain);

	PlayerInputComponent->BindAction("Targeting", EInputEvent::IE_Pressed, this, &ACCombatCharacter::OnTargeting);
	PlayerInputComponent->BindAction("TheWorld", EInputEvent::IE_Pressed, this, &ACCombatCharacter::TheWorld);



	Health = ExtendedHealth->GetCurrentValue() / ExtendedHealth->GetMaxValue();
	Stamina = ExtendedStamina->GetCurrentValue() / ExtendedStamina->GetMaxValue();
	//Mana = ExtendedHealth->GetCurrentValue() / ExtendedHealth->GetMaxValue();

}

void ACCombatCharacter::Progress(float Value)
{
	BlockAlpha = 100 * CurveFloat->GetFloatValue(Value);
}

void ACCombatCharacter::ResetProgress()
{
}

void ACCombatCharacter::UpdateFlightTimeline(UCurveFloat * CurveFloat)
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


USkeletalMeshComponent * ACCombatCharacter::GetSpecificPawnMesh() const
{
	return GetMesh();
}

void ACCombatCharacter::BeginPlay()
{
	Super::BeginPlay();
	//FollowCamera->SetRelativeRotation(StartCameraSettings.Rotation);
	//CameraBoom->TargetArmLength= StartCameraSettings.ArmLength;
	//CameraBoom->SocketOffset = StartCameraSettings.SocketOffset;
	//CameraBoom->CameraLagSpeed = StartCameraSettings.CameraLegSpeed;
	GetCharacterMovement()->bOrientRotationToMovement = true;

	//AI번호
	UAIPerceptionSystem::RegisterPerceptionStimuliSource(this, UAISense_Sight::StaticClass(), this);

	if (PlayerWidgetClass != nullptr)
	{
		
		Widget = CreateWidget(GetWorld(), (PlayerWidgetClass));
		if (Widget != nullptr)
		{
			Widget->AddToViewport();
		}
	}

	FTransform transform = FTransform::Identity;
	FActorSpawnParameters params;
	params.Owner = this;

	SpawnDefaultInventory();

	if (IsValid(ShieldClass))
	{
		Shield = GetWorld()->SpawnActor<ACDisplayedItem>(ShieldClass, transform, params);

	}
	//RetNull(Shield);


	//if (weaponType == E_WeaponType::Sword)
	//	CLog::Print(TEXT("Sword"));
	//if (weaponType == E_WeaponType::Bow)
	//	CLog::Print(TEXT("Bow"));
	//if (weaponType == E_WeaponType::Spell)
	//	CLog::Print(TEXT("Spell"));
	RetNull(DynamicTargeting);
		DynamicTargeting->Initialize(TargetingArrow);
	//RetNull(AttachCamera);
	//AttachCamera->AttachToComponent(CameraBoom, FAttachmentTransformRules::KeepWorldTransform, USpringArmComponent::SocketName);

}

void ACCombatCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateBlock();
	UpdateAimAlpha();
	UpdateState();
	//if (bForward || bRight)
	//{
	//	//	FollowCamera->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
	//	GetCharacterMovement()->bOrientRotationToMovement = true;
	//}
	//else
	//	GetCharacterMovement()->bOrientRotationToMovement = false;


	if (Timeline.IsPlaying())
		Timeline.TickTimeline(DeltaTime);
	//if (bBlock)
	//	timeline->GetTimeline()->Play();
	//else
	//	timeline->GetTimeline()->Reverse();

	UpdateCrosshairPosition();
	//if(combatType != E_CombatType::Unarmed)
		//bUseControllerRotationYaw = true;
	if (GetCharacterMovement()->IsFalling())
		Setfallpoint();
	else
	{
		bcheckfalling = false;
		
	}
	if (GetActorLocation().Z <= 6000)
		FallingReSpawn();

	if (ExtendedStamina->GetCurrentValue() <= 10)
	{
		GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
		ExtendedStamina->bSold = false;

		//return;
	}
}

void ACCombatCharacter::AddWeapon(ACDisplayedItem * Items)
{
	if (Items)
	{
		Item.AddUnique(Items);
	}
}

void ACCombatCharacter::SetCurrentWeapon(class ACDisplayedItem * NewItem, class ACDisplayedItem * LastItem)
{
	ACDisplayedItem* LocalLastItem = NULL;

	if (LastItem != NULL)
	{
		LocalLastItem = LastItem;
	}
	else if (NewItem != CurrentItem)
	{
		LocalLastItem = CurrentItem;
	}

	if (LocalLastItem)
	{
		LocalLastItem->OnUnEquip();
	}

	CurrentItem = NewItem;
	weaponType = CurrentItem->GetWeaponType();
	if (NewItem)
	{
		NewItem->SetOwningPawn(this);
		NewItem->OnEquip(LastItem);
	}
}

void ACCombatCharacter::EquipItem(ACDisplayedItem * Items)
{
	//if (Items->GetWeaponType()==E_WeaponType::Sword)
	if (Items)
	{
		SetCurrentWeapon(Items, CurrentItem);
	}
	//if (Items->GetWeaponType() == E_WeaponType::Sword)
	//{
	//	SetCurrentWeapon(Items, CurrentItem);
	//}
	//if (Items->GetWeaponType() == E_WeaponType::Bow)
	//{
	//	SetCurrentWeapon(Items, CurrentItem);
	//}
	//if (Items->GetWeaponType() == E_WeaponType::Spell)
	//{
	//	SetCurrentWeapon(Items, CurrentItem);
	//}
}

void ACCombatCharacter::SpawnDefaultInventory()
{
	int32 NumItemClasses = ItemClasses.Num();
	//int32 NumSwordClasses = SwordClasses.Num();
	//int32 NumShieldClasses = ShieldClasses.Num();
	//int32 NumBowClasses = BowClasses.Num();
	//int32 NumSpellClasses = SpellClasses.Num();


	for (int32 i = 0; i < NumItemClasses; i++)
	{
		if (ItemClasses[i])
		{
			FActorSpawnParameters SpawnInfo;
			//FTransform transform = FTransform::Identity;
			SpawnInfo.Owner = this;
			ACDisplayedItem* NewItem = GetWorld()->SpawnActor<ACDisplayedItem>(ItemClasses[i], SpawnInfo);
			AddWeapon(NewItem);
			EquipItem(Item[i]);
		}
	}
	EquipItem(Item[0]);
	//CurrentItem = Item[0];
	//weaponType = CurrentItem->GetWeaponType();
	//if (Item[0])
	//{
	//	Item[0]->SetOwningPawn(this);
	//	Item[0]->OnEquip(CurrentItem);
	//}
	//for (int32 i = 0; i < NumSwordClasses; i++)
	//{
	//	if (SwordClasses[i])
	//	{
	//		FActorSpawnParameters SpawnInfo;
	//		ACDisplayedItem* NewItem = GetWorld()->SpawnActor<ACDisplayedItem>(SwordClasses[i], SpawnInfo);
	//		AddWeapon(NewItem);
	//	}
	//}
	//if (Swords[0])
	//{
	//	EquipItem(Swords[0]);
	//}
	//for (int32 i = 0; i < NumShieldClasses; i++)
	//{
	//	if (ShieldClasses[i])
	//	{
	//		FActorSpawnParameters SpawnInfo;
	//		ACDisplayedItem* NewItem = GetWorld()->SpawnActor<ACDisplayedItem>(ShieldClasses[i], SpawnInfo);
	//		AddWeapon(NewItem);
	//	}
	//}
	//if (Shields[0])
	//{
	//	EquipItem(Shields[0]);
	//}
	//for (int32 i = 0; i < NumBowClasses; i++)
	//{
	//	if (BowClasses[i])
	//	{
	//		FActorSpawnParameters SpawnInfo;
	//		ACDisplayedItem* NewItem = GetWorld()->SpawnActor<ACDisplayedItem>(BowClasses[i], SpawnInfo);
	//		AddWeapon(NewItem);
	//	}
	//}
	//if (Bows[0])
	//{
	//	EquipItem(Bows[0]);
	//}
	//for (int32 i = 0; i < NumSpellClasses; i++)
	//{
	//	if (SpellClasses[i])
	//	{
	//		FActorSpawnParameters SpawnInfo;
	//		ACDisplayedItem* NewItem = GetWorld()->SpawnActor<ACDisplayedItem>(SpellClasses[i], SpawnInfo);
	//		AddWeapon(NewItem);
	//	}
	//}
	//if (Spells[0])
	//{
	//	EquipItem(Spells[0]);
	//}

	//CurrentItem = Item[0];
	//weaponType = CurrentItem->GetWeaponType();

	//if (Item[0])
	//{
	//	
	//}

	//if (Item.Num() > 0)
	//{
	//	EquipItem(Item[0]);
	//}
}

void ACCombatCharacter::OnChangeItem(int num)
{
	int32 ItemIndex = Item.IndexOfByKey(CurrentItem);
	if (ItemIndex == 0)
		ItemIndex = Item.Num();
	ACDisplayedItem* NextItem = Item[(ItemIndex + num) % Item.Num()];
	weaponType = NextItem->GetWeaponType();
	//if (weaponType == E_WeaponType::Sword)
	//	CLog::Print(TEXT("Sword"));
	//if (weaponType == E_WeaponType::Bow)
	//	CLog::Print(TEXT("Bow"));
	//if (weaponType == E_WeaponType::Spell)
	//	CLog::Print(TEXT("Spell"));
	EquipItem(NextItem);
	if (combatType == E_CombatType::Melee)
	{
		Equip();
	}

}

void ACCombatCharacter::WeaponChangeUp()
{
	OnChangeItem(1);
}

void ACCombatCharacter::WeaponChangeDown()
{
	OnChangeItem(-1);
}


void ACCombatCharacter::UpdateAimAlpha()
{
	if (StateManager->GetActivityValue(E_Activity::IsAimingPressed))
	{
		AimAlpha = FMath::FInterpConstantTo(AimAlpha, 1.0f, UGameplayStatics::GetWorldDeltaSeconds(this), 3.0f);
		StateManager->SetState(E_State::Attacking);
		CurrentItem->SetAimAlpha(AimAlpha);
		if(IsValid(PlayerWidget->GetCrosshair()))
			PlayerWidget->GetCrosshair()->SetCrosshairVisibility(true);
	}
	else if (StateManager->GetActivityValue(E_Activity::IsBlockingPressed))
	{
		//AimAlpha = FMath::FInterpConstantTo(AimAlpha, 1.0f, UGameplayStatics::GetWorldDeltaSeconds(this), 3.0f);
		//StateManager->SetState(E_State::Attacking);
		//CurrentItem->SetAimAlpha(AimAlpha);
		if (IsValid(PlayerWidget->GetCrosshair()))
			PlayerWidget->GetCrosshair()->SetCrosshairVisibility(true);
	}
	else if (StateManager->GetActivityValue(E_Activity::None))
	{
		AimAlpha = FMath::FInterpConstantTo(AimAlpha, 0.0f, UGameplayStatics::GetWorldDeltaSeconds(this), 3.0f);
		CurrentItem->SetAimAlpha(0);
		if (IsValid(PlayerWidget->GetCrosshair()))
			PlayerWidget->GetCrosshair()->SetCrosshairVisibility(false);

	}
	if (AimAlpha >= 1)
		bShoot = true;
	else
		bShoot = false;

}

void ACCombatCharacter::UpdateBlock()
{
	if (IsValid(Shield))
	{
		if (bShieldEquipped == true)
			Shield->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), "shield_use");
		else if (bShieldEquipped == false)
			Shield->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), "shield");
		
		if (StateManager->GetState() == E_State::Idle && StateManager->GetActivityValue(E_Activity::IsBlockingPressed))
			StateManager->SetState(E_State::Blocking);
		//if (StateManager->GetActivityValue(E_Activity::IsBlockingPressed))
		//{
		//	RetNull(PlayerWidget->GetCrosshair());
		//	if (StateManager->GetState() == E_State::Parrying)
		//		PlayerWidget->GetCrosshair()->SetCrosshairVisibility(true);
		//	else
		//		PlayerWidget->GetCrosshair()->SetCrosshairVisibility(false);
		//}

	}

}

void ACCombatCharacter::UpdateCrosshairPosition()
{
	RetNull(Widget);
	PlayerWidget = Cast<UPlayerWidget>(Widget);
	RetNull(PlayerWidget);
	RetNull(PlayerWidget->GetCrosshair());
	if (PlayerWidget->GetCrosshair()->GetVisibility() == ESlateVisibility::HitTestInvisible)
	{		
		if (weaponType == E_WeaponType::Bow)
		{
			WorldVector = ArrowLocation->GetComponentLocation()
				+ (FQuat(ArrowLocation->GetComponentRotation()).GetForwardVector() * 500);
		}
		else if (weaponType == E_WeaponType::Sword)
		{
			WorldVector = ArrowShootLocation->GetComponentLocation()
				+ (FQuat(ArrowLocation->GetComponentRotation()).GetForwardVector() * 500);
		}

		PlayerWidget->GetCrosshair()->SetCrosshairPosition(WorldVector);
	}
		
}

void ACCombatCharacter::UpdateState()
{
	if (StateManager->GetState() == E_State::Attacking)
	{
		bUseControllerRotationYaw = true;
	}
	else if (StateManager->GetState() == E_State::Idle)
	{
		//bUseControllerRotationYaw = true;

	}
}



void ACCombatCharacter::GetAttackCount()
{

	StateManager->SetState(E_State::Idle);
}

void ACCombatCharacter::OnMoveForward(float Value)
{
	if (StateManager->GetState() == E_State::Dead)	return;
	if (StateManager->GetState() == E_State::SpecialMagic)	return;

	//if (bCanMove == false) return;
	//if (StateManager->GetState() != E_State::Idle) return;
	bForward = Value != 0.0f;

	//ACCameraActor* ACamera;
	//AActor* Camera = UGameplayStatics::GetPlayerController(this, 0)->GetViewTarget();
	
	//FRotator rotation = Camera->GetActorRotation();
	FRotator rotation = GetControlRotation();
	//FRotator rotation = GetActorRotation();

	FRotator temp = FRotator(0, rotation.Yaw, 0);
	FVector forward = FQuat(temp).GetForwardVector();
	FVector up = FQuat(temp).GetUpVector();
	if (bGrabRope)
		MyRope->AddSwingforce(forward*500* Value);
	else
		AddMovementInput(forward, Value);
		//FollowCamera->AttachToComponent(CameraBoom, FAttachmentTransformRules::KeepWorldTransform);
	//if (bUp)
	//{
	//	//	FollowCamera->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
	//	GetCharacterMovement()->bOrientRotationToMovement = true;
	//}
	//else
	//	GetCharacterMovement()->bOrientRotationToMovement = false;


	AddMovementInput(up, Value);
	GetFoward = Value;
	//ACamera = Cast<ACCameraActor>(Camera);
	//if(ACamera->GetCameraSide() == E_CameraSide::FrontSide)
	//	Camera->SetActorLocation(CameraBoomSide->GetSocketLocation(USpringArmComponent::SocketName), false, 0, ETeleportType::None);
	//if (ACamera->GetCameraSide() == E_CameraSide::RightSide)
	//	Camera->SetActorLocation(CameraBoom->GetSocketLocation(USpringArmComponent::SocketName), false, 0, ETeleportType::None);

		//if (bForward)
		//	Camera->AttachToComponent(CameraBoom, FAttachmentTransformRules::KeepWorldTransform);
		//else
		//	Camera->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	//GetTest();

	//if (GetTest() == false)
	//	Camera->AttachToComponent(CameraBoom, FAttachmentTransformRules::KeepWorldTransform);		//
	//else if (GetTest() == true)
	//	Camera->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
}

void ACCombatCharacter::OnMoveRight(float Value)
{
	if (StateManager->GetState() == E_State::Dead)	return;
	if (StateManager->GetState() == E_State::SpecialMagic)	return;

	//if (bCanMove == false) return;
	bRight = Value != 0.0f;

	//if (StateManager->GetState() != E_State::Idle) return;

	//AActor* Camera = UGameplayStatics::GetPlayerController(this, 0)->GetViewTarget();
	//FRotator rotation = Camera->GetActorRotation();
	FRotator rotation = GetControlRotation();
	//FRotator rotation = GetActorRotation();
	FRotator temp = FRotator(0, rotation.Yaw, 0);
	FVector right = FQuat(temp).GetRightVector();

	if (bGrabRope)
		MyRope->AddSwingforce(right * 500 * Value);
	else
		AddMovementInput(right, Value);
	//
	GetRight = Value;

	//GetTest();

	//Camera->SetActorLocationAndRotation();
	//Camera->SetActorLocation(CameraBoom->GetSocketLocation(USpringArmComponent::SocketName), false, 0, ETeleportType::None);

	//if(GetTest() == false)
	//	Camera->AttachToComponent(CameraBoom, FAttachmentTransformRules::KeepWorldTransform);		//
	//else if(GetTest() == true)
	//	Camera->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

}

void ACCombatCharacter::OnTurn(float Value)
{
	if (StateManager->GetState() == E_State::Dead)	return;
	float LookatPitch = Value;
	if (GetStateManager()->GetActivityValue(E_Activity::IsAimingPressed))
	{
		LookatPitch = Value * 0.5;
		AddControllerYawInput(LookatPitch);
	}
	else
		AddControllerYawInput(LookatPitch);
	RetNull(DynamicTargeting);
	//DynamicTargeting->FindTargetWithAxisInput(LookatPitch);
}

void ACCombatCharacter::OnLookUp(float Value)
{
	if (StateManager->GetState() == E_State::Dead)	return;
	float LookatYaw = Value;
	if (GetStateManager()->GetActivityValue(E_Activity::IsAimingPressed))
	{
		LookatYaw = Value * 0.5;
		AddControllerPitchInput(LookatYaw);
		
	}
	else
		AddControllerPitchInput(LookatYaw);
	//RetNull(DynamicTargeting);
	//DynamicTargeting->FindTargetWithAxisInput(LookatYaw);
	//CalculateLeanAmount();
}

void ACCombatCharacter::OnZoom(float Value)
{
	CameraBoom->TargetArmLength += (ZoomSpeed * Value);
	if (CameraBoom->SocketOffset.Z >= 10)
		CameraBoom->SocketOffset.Z += (10 * Value);
	else
		CameraBoom->SocketOffset.Z = 10;
}

void ACCombatCharacter::OnRunning()
{
	if (ExtendedStamina->GetCurrentValue() <= 10)
	{
		return;
	}
	GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
	ExtendedStamina->bSold = true;
	bRuning = true;
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
}

void ACCombatCharacter::OffRunning()
{
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	ExtendedStamina->bSold = false;
	bUseControllerRotationYaw = true;
	GetCharacterMovement()->bOrientRotationToMovement = false;

	GetWorldTimerManager().SetTimer(DashTimerHandle, this, &ACCombatCharacter::enddash, 0.2f, false);
	

}

void ACCombatCharacter::OnJumping()
{
	if (StateManager->GetState() == E_State::Dead)	return;
	if (bCanMove == false) return;
	FLatentActionInfo info = FLatentActionInfo();
	info.CallbackTarget = this;
	//UKismetSystemLibrary::MoveComponentTo(GetCapsuleComponent(),GetActorLocation() + GetActorForwardVector() * 300, FRotator(0, 0, GetActorForwardVector().Rotation().Yaw), false, false, 0.5, false, EMoveComponentAction::Move, info);
	if (bGrabRope)
	{
		OnUnGrabRope();
		//return;
	}
	Jump();
}

void ACCombatCharacter::OnRolling()
{
	if (StateManager->GetState() == E_State::Dead)	return;
	//if (bCanMove == false) return;
	if (StateManager->GetState() == E_State::Rolling) return;
	if (ExtendedStamina->GetCurrentValue() <= 10) return;

	GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
	bCanMove = false;
	StateManager->SetState(E_State::Rolling);
	if (GetFoward >= 0 && GetRight == 0)//fornt
	{
		if (weaponType == E_WeaponType::Bow)
		{
			RetNull(Roll_F_Montage);
			PlayAnimMontage(Roll_F_Montage, 1.5f);
			
		}
		else
		{
			RetNull(Dash_F_Montage);
			PlayAnimMontage(Dash_F_Montage, 1.f);

		}
	}
	if (GetFoward < 0 && GetRight == 0)//back
	{
		if (weaponType == E_WeaponType::Bow)
		{
			RetNull(Roll_B_Montage);
			PlayAnimMontage(Roll_B_Montage, 1.5f);
		}
		else
		{
			RetNull(Dash_B_Montage);
			PlayAnimMontage(Dash_B_Montage, 1.f);

		}
	}
	if (GetRight > 0) //&& GetFoward == 0  )//right
	{
		if (weaponType == E_WeaponType::Bow)
		{
			RetNull(Roll_R_Montage);
			PlayAnimMontage(Roll_R_Montage, 1.5f);
		}
		else
		{
			RetNull(Dash_R_Montage);
			PlayAnimMontage(Dash_R_Montage, 1.f);

		}
	}
	if (GetRight < 0) //&& GetFoward == 0)//left
	{
		if (weaponType == E_WeaponType::Bow)
		{
			RetNull(Roll_L_Montage);
			PlayAnimMontage(Roll_L_Montage, 1.5f);
		}
		else
		{
			RetNull(Dash_L_Montage);
			PlayAnimMontage(Dash_L_Montage, 1.f);

		}
	}
	ExtendedStamina->ModifyStat(-15, true);
	//if (GetFoward > 0 && GetRight > 0)//fr
	//{
	//	RetNull(Roll_FR_Montage);
	//	PlayAnimMontage(Roll_FR_Montage, 1.5f);
	//}
	//if (GetFoward > 0 && GetRight < 0)//fl
	//{
	//	RetNull(Roll_FL_Montage);
	//	PlayAnimMontage(Roll_FL_Montage, 1.5f);
	//}
	//if (GetFoward < 0 && GetRight > 0)//br
	//{
	//	RetNull(Roll_BR_Montage);
	//	PlayAnimMontage(Roll_BR_Montage, 1.5f);
	//}
	//if (GetFoward < 0 && GetRight < 0)//bl
	//{
	//	RetNull(Roll_BL_Montage);
	//	PlayAnimMontage(Roll_BL_Montage, 1.5f);
	//}


}

void ACCombatCharacter::OnEquip()
{
	//if (combatType != E_CombatType::Unarmed) return;
	if (StateManager->GetState() == E_State::Dead)	return;
	if (StateManager->GetState() != E_State::Idle) return;
	if (StateManager->GetState() == E_State::Drawing || StateManager->GetState() == E_State::Sheathing) return;
	if (bDrawn == false)
	{
		Equip();

		return;
	}

	if (GetCharacterMovement()->IsFalling() == false)
		Sheath();
}

void ACCombatCharacter::OnAttacking()
{
	if (StateManager->GetState() == E_State::Dead)	return;
	if (bDrawn == false) return;
	//if (bAttacking == true) return;
	if (StateManager->GetState() == E_State::Attacking) return;
	if (StateManager->GetState() == E_State::Parrying)
	{
		RetNull(ParryAttackMontage1);
		PlayAnimMontage(ParryAttackMontage1, 1.5);
	}
	else
		StateManager->SetState(E_State::Attacking);

	if (StateManager->GetState() == E_State::Parrying) return;
	if (weaponType == E_WeaponType::Sword)
	{
		bCanMove = false;
		if (AttackCount == 0)
		{
			if (StateManager->GetState() == E_State::Rolling || bRuning)
			{
				RetNull(AttackChargeMontage2_1);
				PlayAnimMontage(AttackChargeMontage2_1, 1, FName("start"));
			}
			else
			{
				RetNull(AttackComboMontage1);
				PlayAnimMontage(AttackComboMontage1, 1.2);

			}
		}
		if (AttackCount == 1)
		{
			RetNull(AttackComboMontage2);
			PlayAnimMontage(AttackComboMontage2, 1.2);
		}
		if (AttackCount == 2)
		{
			RetNull(AttackComboMontage3);
			PlayAnimMontage(AttackComboMontage3, 1.2);
		}
		if (AttackCount == 3)
		{
			RetNull(AttackComboMontage4);
			PlayAnimMontage(AttackComboMontage4, 1.2);
		}
		if (AttackCount == 4)
		{
			RetNull(AttackComboMontage5);
			PlayAnimMontage(AttackComboMontage5, 1.4);
		}
		//ExtendedStamina->ModifyStat(-15, true);

	}
	if (weaponType == E_WeaponType::Bow)
		OnAiming();
	if (weaponType == E_WeaponType::Spell)
		OnMagic();
	//GetStateManager()->SetActivity(E_Activity::IsAimingPressed,true)
//if (AttackCount == 0)
//{
//	
//}
}

void ACCombatCharacter::OnCharge()
{
	if (StateManager->GetState() == E_State::Dead)	return;
	if (bDrawn == false) return;
	//if (bAttacking == true) return;
	if (StateManager->GetState() == E_State::Attacking) return;
	if (ExtendedStamina->GetCurrentValue() <= 10) return;
	if (StateManager->GetState() == E_State::Parrying)
	{
		RetNull(ParryAttackMontage2);
		PlayAnimMontage(ParryAttackMontage2, 1, FName("start"));
	}
	else
		StateManager->SetState(E_State::Attacking);
	if (StateManager->GetState() == E_State::Parrying) return;
	//bImotal = true;
	if (AttackCount == 0)
	{
		if (StateManager->GetState() == E_State::Rolling || bRuning)
		{
			RetNull(AttackChargeMontage4_1);
			PlayAnimMontage(AttackChargeMontage4_1, 1.2);

		}
		else
		{
			RetNull(AttackChargeMontage1_1);
			PlayAnimMontage(AttackChargeMontage1_1, 1.2);
			ExtendedStamina->ModifyStat(-30, true);
		}
	}
	if (AttackCount == 1)
	{
		RetNull(AttackChargeMontage2_1);
		PlayAnimMontage(AttackChargeMontage2_1, 1,FName("start"));
	}
	if (AttackCount == 2)
	{
		RetNull(AttackChargeMontage3_1);
		PlayAnimMontage(AttackChargeMontage3_1, 1.2);
	}
	if (AttackCount == 3)
	{
		RetNull(AttackChargeMontage4_1);
		PlayAnimMontage(AttackChargeMontage4_1, 1.2);
	}
	if (AttackCount == 4)
	{
		RetNull(AttackChargeMontage5_1);
		PlayAnimMontage(AttackChargeMontage5_1, 1.2);
	}
	ExtendedStamina->ModifyStat(-30, true);

}

void ACCombatCharacter::OnSwing()
{
	UGameplayStatics::PlaySoundAtLocation(this, SwingSound, GetActorLocation());
	//if (WindBladeClass != NULL)
	//{
	//	UWorld* const World = GetWorld();
	//	if (World != NULL)
	//	{
	//		const FRotator SpawnRotation = GetControlRotation();
	//		const FVector SpawnLocation = WindBladeLocation->GetComponentLocation();// +FVector(100.0f, 0.0f, 10.0f);
	//		FActorSpawnParameters ActorSpawnParams;
	//		ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
	//		//if (IsValid(ArrowClass))
	//		World->SpawnActor<ACWindBlade>(WindBladeClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
	//	}
	//}
	//if (FireStormClass != NULL)
	//{
	//	UWorld* const World = GetWorld();
	//	if (World != NULL)
	//	{
	//		const FRotator SpawnRotation;
	//		const FVector SpawnLocation = WindBladeLocation->GetComponentLocation();// +FVector(100.0f, 0.0f, 10.0f);
	//		FActorSpawnParameters ActorSpawnParams;
	//		ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
	//		//if (IsValid(ArrowClass))
	//		World->SpawnActor<ACFireStorm>(FireStormClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
	//	}
	//}
}

void ACCombatCharacter::OffAttacking()
{
	//CLog::Print(TEXT("OffAttacking"));
	if (weaponType == E_WeaponType::Bow)
	{
		if (GetStateManager()->GetActivityValue(E_Activity::IsAimingPressed) && bShoot)
		{
			RetNull(ShoothMontage);
			PlayAnimMontage(ShoothMontage, 1.5f);
		}
		else if (!bShoot)
			OffAiming();
	}
	 
}

void ACCombatCharacter::OnBlocking()
{
	if (StateManager->GetState() == E_State::Dead)	return;
	GetCharacterMovement()->MaxWalkSpeed = BlockSpeed;
	if (combatType != E_CombatType::Melee)
		return;

	GetStateManager()->SetActivity(E_Activity::IsBlockingPressed, true);
	if (bShieldEquipped)
	{
		UpdateFlightTimeline(CurveFloat);
		Timeline.Play();
	}
	//StateManager->SetState(E_State::Blocking);
	if (weaponType == E_WeaponType::Sword)
	{
		if (bShieldEquipped == true)
		{
			RetNull(HS_BlockMontage);
			PlayAnimMontage(HS_BlockMontage, 1.f);
		}
		else
		{
			RetNull(H_BlockMontage);
			PlayAnimMontage(H_BlockMontage, 1.f);
		}
	}
	if (weaponType == E_WeaponType::Spell)
	{
		RetNull(MS_BlockMontage);
		PlayAnimMontage(MS_BlockMontage, 1.5f);

	}
}

void ACCombatCharacter::OffBlocking()
{
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	//if (StateManager->GetState() != E_State::Blocking) return;
	OnEndBlock.Broadcast();
	bCanMove = true;
	GetStateManager()->SetActivity(E_Activity::IsBlockingPressed, false);


	ResetState();
	Timeline.Reverse();

}

void ACCombatCharacter::OnAiming()
{
	if (StateManager->GetState() == E_State::Dead)	return;
	GetCharacterMovement()->bOrientRotationToMovement = false;
	//CameraBoom->TargetArmLength = 500;
	FollowCamera->SetRelativeLocation(FVector(340, 0, -20));
	FollowCamera->SetRelativeRotation(FRotator(0, 0, 0));

	if (AimAlpha == 0)
		GetStateManager()->SetActivity(E_Activity::IsAimingPressed, true);
	
	StateManager->SetState(E_State::Aiming);
	UpdateFlightTimeline(CurveFloat);
	
	Timeline.Play();
	OnSpawnArrow();
	Arrow->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepWorld, true), "bow_string");
	//Shield->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), "shield_use");


	RetNull(ArrowDrawMontage);
	PlayAnimMontage(ArrowDrawMontage, 1.f);

}

void ACCombatCharacter::OffAiming()
{
	GetStateManager()->SetActivity(E_Activity::IsAimingPressed, false);
	ResetState();
}

void ACCombatCharacter::OnMagic()
{
	if (StateManager->GetState() == E_State::Dead)	return;
	if (magicType == E_MagicType::Fireball)
	{
		if (AttackCount == 0)
		{
			RetNull(FireballMontage);
			PlayAnimMontage(FireballMontage, 1.f);
		}
		if (AttackCount == 1)
		{
			RetNull(FireballMontage2);
			PlayAnimMontage(FireballMontage2, 1.f);
		}
		if (AttackCount == 2)
		{
			RetNull(FireballMontage3);
			PlayAnimMontage(FireballMontage3, 1.f);
		}
	}


}

void ACCombatCharacter::OnMagicNum1()
{
	magicType = E_MagicType::Fireball;
	CLog::Print(TEXT("Fireball"));
	OnMagicChange();
}

void ACCombatCharacter::OnMagicNum2()
{
	magicType = E_MagicType::Heal;
	CLog::Print(TEXT("Heal"));
	OnMagicChange();
}

void ACCombatCharacter::OnMagicNum3()
{
	magicType = E_MagicType::Strom;
	CLog::Print(TEXT("Strom"));
	OnMagicChange();
}

void ACCombatCharacter::OnMagicNum4()
{
	magicType = E_MagicType::Boom;
	CLog::Print(TEXT("Boom"));
	OnMagicChange();
}

void ACCombatCharacter::OnMagicNum5()
{
	magicType = E_MagicType::Burf;
	CLog::Print(TEXT("Burf"));
	OnMagicChange();
}

void ACCombatCharacter::OnMagicChange()
{
	if (combatType == E_CombatType::Melee)
		Equip();

	//GetSword()->ChangeSpell();
}

void ACCombatCharacter::OnFlying()
{
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Flying);
}

void ACCombatCharacter::OffFlying()
{
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
}

void ACCombatCharacter::OnDrawArrow()
{

}

void ACCombatCharacter::OnShoot()
{
	if (StateManager->GetState() == E_State::Dead)	return;
	if (weaponType == E_WeaponType::Sword)
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
	
	if (weaponType == E_WeaponType::Bow)
	{
		//OnSpawnArrow();
		RetNull(Arrow);
		Arrow->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		TArray<AActor*> AtI;
		FHitResult HitResult;
		//UKismetSystemLibrary::LineTraceSingle(GetWorld(), Arrow->GetActorLocation(), Arrow->GetActorLocation() + FQuat(Arrow->GetActorRotation()).GetForwardVector()*4000,ETraceTypeQuery::TraceTypeQuery3,false, AtI,EDrawDebugTrace::Persistent,HitResult,true);
		//for (FHitResult a : HitResult)
		//{
		//}
		Arrow->OnShoot(FVector(0,0,0));
		Arrow = NULL;

	}
	if (weaponType == E_WeaponType::Spell && magicType == E_MagicType::Fireball)
	{
		if (FireballClass != NULL)
		{
			UWorld* const World = GetWorld();
			if (World != NULL)
			{
				const FRotator SpawnRotation = GetControlRotation();
				//const FVector SpawnLocation = ShootRightLocation->GetComponentLocation();// +FVector(100.0f, 0.0f, 10.0f);

				const FVector SpawnLocation = (AttackCount == 1) ?
					ShootLeftLocation->GetComponentLocation() : ShootRightLocation->GetComponentLocation();// +FVector(100.0f, 0.0f, 10.0f);
				FActorSpawnParameters ActorSpawnParams;
				ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
				RetNull(FireballClass);
				World->SpawnActor<ACFireball>(FireballClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
			}
		}
	}
}

void ACCombatCharacter::Equip()
{
	if (StateManager->GetState() == E_State::Dead)	return;
	ResetState();
	StateManager->SetState(E_State::Drawing);
	bDrawing = true;
	bCanMove = false;
	if (weaponType == E_WeaponType::Sword)
	{
		RetNull(EquipSwordMontage);
		PlayAnimMontage(EquipSwordMontage, 1.5f);

	}
	if (weaponType == E_WeaponType::Bow)
	{
		RetNull(EquipBowMontage);
		PlayAnimMontage(EquipBowMontage, 1.5f);
	}
	if (weaponType == E_WeaponType::Spell)
	{
		RetNull(EquipSpellMontage);
		PlayAnimMontage(EquipSpellMontage, 1.5f);
	}
	RetNull(Arrow);
	Arrow->DetachFromActor(FDetachmentTransformRules(EDetachmentRule::KeepWorld, true));
	Arrow->DestroyArrow();
	Arrow = NULL;
	GetStateManager()->SetActivity(E_Activity::IsAimingPressed, false);


}

void ACCombatCharacter::Sheath()
{
	if (StateManager->GetState() == E_State::Dead)	return;
	ResetState();
	StateManager->SetState( E_State::Sheathing);
	bSheathing = true;
	if (weaponType == E_WeaponType::Sword)
	{
		RetNull(SheathSwordMontage);
		PlayAnimMontage(SheathSwordMontage, 1.f);

	}
	if (weaponType == E_WeaponType::Bow)
	{
		RetNull(SheathBowMontage);
		PlayAnimMontage(SheathBowMontage, 1.f);
	}
	if (weaponType == E_WeaponType::Spell)
	{
		RetNull(SheathSpellMontage);
		PlayAnimMontage(SheathSpellMontage, 1.5f);

	}
	RetNull(Arrow);
	Arrow->DetachFromActor(FDetachmentTransformRules(EDetachmentRule::KeepWorld, true));
	Arrow->DestroyArrow();
	Arrow = NULL;
	GetStateManager()->SetActivity(E_Activity::IsAimingPressed, false);

}

void ACCombatCharacter::Roll()
{
}

void ACCombatCharacter::Blocking()
{
	BlockAlpha = 100;
}

void ACCombatCharacter::Equipped()
{
	bDrawing = false;
	bDrawn = true;
	combatType = E_CombatType::Melee;
	StateManager->SetState(E_State::Idle);
	bCanMove = true;
	//bUseControllerRotationYaw = false;

	//GetCharacterMovement()->bOrientRotationToMovement = true;
	//GetCharacterMovement()->MaxWalkSpeed = 400.0f;
	if (IsValid(Shield))
	if (weaponType == E_WeaponType::Sword || weaponType == E_WeaponType::Spell)
	{
		bShieldEquipped = true;
	}
	else
	{
		bShieldEquipped = false;
	}
}

void ACCombatCharacter::Sheathed()
{
	bSheathing = false;
	bDrawn = false;
	combatType = E_CombatType::Unarmed;
	ResetState();

	//bUseControllerRotationYaw = false;
	//GetCharacterMovement()->bOrientRotationToMovement = true;
	//GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	bShieldEquipped = false;
}

void ACCombatCharacter::BeginAttack()
{
	StateManager->SetState(E_State::Attacking);
}

void ACCombatCharacter::EndAttack()
{
	AttackCount = AttackCount + 1;
	//CLog::Print(AttackCount);
	StateManager->SetState(E_State::Idle);
}

void ACCombatCharacter::ResetState()
{
	if (StateManager->GetState() == E_State::Dead)	return;
	StateManager->SetState(E_State::Idle);
	bCanMove = true;
	FollowCamera->SetRelativeLocation(FVector(-165, 0, 35));
	FollowCamera->SetRelativeRotation(FRotator(-10, 0, 0));
	//Shield->OnUnEquip();
	//Timeline.Reverse();
	AttackCount = 0;
	GetStateManager()->SetActivity(E_Activity::None, true);
	//GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	//GetCharacterMovement()->bOrientRotationToMovement = false;
	CameraBoom->TargetArmLength = 300;
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1.0);
	bImotal = false;
}

void ACCombatCharacter::BeginBlock()
{
	StateManager->SetState(E_State::Blocking);
	bCanMove = false;
}

void ACCombatCharacter::EndBlock()
{
	StateManager->SetState(E_State::Idle);
	OffBlocking();
}

float ACCombatCharacter::TakeDamage(float Damage, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	if (DamageCauser == this) return 0;
	if (StateManager->GetState() == E_State::Dead)	return 0;
	if (StateManager->GetState() == E_State::Parrying)	return 0;
	if (StateManager->GetState() == E_State::Blocking)
	{
		Parrying();
		return 0;
	}
	if (StateManager->GetState() == E_State::Damage) return 0;
	ExtendedHealth->ModifyStat(-Damage, false);
	StateManager->SetState(E_State::Damage);
	GetWorldTimerManager().SetTimer(DamageTimerHandle, this, &ACCombatCharacter::ResetState, 0.1f, false);

	UGameplayStatics::PlaySoundAtLocation(this, PainSound, GetActorLocation());
	if (DamageCauser->IsA(ACEnemy::StaticClass()))
	{
		FVector VSocket = FVector(0, 0, 0);
		if (Cast<ACEnemy>(DamageCauser)->GetEnemyType() == E_EnemyType::SwordMan)
		{
			VSocket = Cast<ACEnemy>(DamageCauser)->GetSword()->GetWeaponMesh()->GetSocketLocation("Socket_6");
		}
		FVector VActor = GetActorLocation();
		FVector Normalize =
			VActor + UKismetMathLibrary::Normal(VSocket - VActor) * 40;
		if (IsValid(Blood))
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Blood, Normalize);

		}
		//폭발맞을때 에러
	}
	if (ExtendedHealth->GetCurrentValue() <= 0)
	{
		Dead();
		return Damage;
	}

	OnHitReaction();
	BloodSpilt();

	return Damage;
}

void ACCombatCharacter::Parrying()
{
	StateManager->SetState(E_State::Parrying);
	UGameplayStatics::PlaySoundAtLocation(this, ParrySound, GetActorLocation());

	//PlayerWidget->GetCrosshair()->SetCrosshairVisibility(true);
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 0.3);
	GetWorldTimerManager().SetTimer(CountdownTimerHandle, this, &ACCombatCharacter::ResetState, 0.3f, false);


	//RetNull(AttackComboMontage3);
	//PlayAnimMontage(AttackComboMontage3, 1.5f);
	//OffBlocking();
}
void ACCombatCharacter::BloodSpilt()
{
	if (bImotal) return;
	FVector Spawnlocation = GetActorLocation();
	Spawnlocation.X -= 50;
	Spawnlocation.Y -= 50;
	Spawnlocation.Z += 50;

	FollowCamera->PostProcessSettings.ColorGain = FVector4(2, 1, 1, 1);
	UGameplayStatics::GetPlayerController(this,0)->PlayerCameraManager->PlayCameraShake(MyShake, 1.0f);
	//GetWorld()->GetFirstPlayerController()->PlayerCameraManager->PlayCameraShake(MyShake, 1.0f);
	//UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Blood,
	//	Spawnlocation, FRotator(0, 0, 0), FVector(2, 2, 2), true, EPSCPoolMethod::None);
}

void ACCombatCharacter::OnHitReaction()
{
	GetWorldTimerManager().SetTimer(CountdownTimerHandle, this, &ACCombatCharacter::OnCollision, 0.5f, false);
	if (!bImotal)
	{
		StateManager->SetState(E_State::Damage);
		RetNull(HitReractionMontage);
		PlayAnimMontage(HitReractionMontage, 1.f);
		RetNull(Arrow);
		Arrow->DetachFromActor(FDetachmentTransformRules(EDetachmentRule::KeepWorld, true));
		Arrow->DestroyArrow();
		Arrow = NULL;
	}
}

void ACCombatCharacter::Dead()
{
	StateManager->SetState(E_State::Dead);
	RetNull(DeadMontage);
	PlayAnimMontage(DeadMontage, 1.0);
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}
void ACCombatCharacter::SetCamera()
{
	//if()
	UGameplayStatics::GetPlayerController(this, 0)->SetViewTarget(FollowCamera->GetOwner());

}

void ACCombatCharacter::GoRight(float Value)
{
	SetActorRelativeRotation(FRotator(0, 0, 0));
	OnMoveForward(Value);
}

void ACCombatCharacter::GoLeft(float Value)
{
	SetActorRelativeRotation(FRotator(0, 180, 0));
	OnMoveForward(Value);

}

void ACCombatCharacter::GoUp(float Value)
{
	SetActorRelativeRotation(FRotator(0, 90, 0));
	OnMoveForward(Value);

}

void ACCombatCharacter::GoDown(float Value)
{
	SetActorRelativeRotation(FRotator(0, 270, 0));
	OnMoveForward(Value);

}

void ACCombatCharacter::GetAttachCamera(AActor * Camera)
{
	RetNull(Camera);
	Camera->AttachToComponent(CameraBoom, FAttachmentTransformRules::KeepRelativeTransform, USpringArmComponent::SocketName);
	//Camera->SetActorLocationAndRotation(CameraBoom->GetComponentLocation(), CameraBoom->GetComponentRotation());

}

void ACCombatCharacter::GetDetachCamera(AActor * Camera)
{
	Camera->DetachRootComponentFromParent(false);
}

void ACCombatCharacter::OnCapsuleBeginOverlap(UPrimitiveComponent * OverlapComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	RetNull(OtherActor);
	RetNull(OtherComp);
	if (OtherActor == this)return;

	//if (OtherActor->GetClass()->IsChildOf(ACameraChangeTrigger::StaticClass()))
	//{
	//	ChangeCamera = Cast<ACameraChangeTrigger>(OtherActor);

	//	UGameplayStatics::GetPlayerController(this, 0)->SetViewTargetWithBlend(ChangeCamera->GetCamera(), 0.75);
	////	if (!player->GetTest())
	//		//Camera->AttachToComponent(PlayerCamera, FAttachmentTransformRules::KeepWorldTransform);		//
	//	//else
	//	//	Camera->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

	//}

}

void ACCombatCharacter::OnCapsuleEndOverlap(UPrimitiveComponent * OverlapComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	RetNull(OtherActor);
	RetNull(OtherComp);
	if (OtherActor == this)return;

	//if (ChangeCamera != NULL)
	//{
	//	ChangeCamera = NULL;
	//}
}

bool ACCombatCharacter::GetTest()
{
	//CLog::Print(TEXT("Test"));
	
	FVector2D ScreemLocation;
	
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->ProjectWorldLocationToScreen(GetActorLocation(), ScreemLocation);
	//if (!UKismetMathLibrary::InRange_FloatFloat(ScreemLocation.Y, 490, 500))
	//{
	//	if (ScreemLocation.Y < 490)
	//		if (GetFoward < -0.1)
	//			return false;
	//		else
	//			return true;
	//	else if (ScreemLocation.Y > 500)
	//		if (GetFoward > 0.1)
	//			return false;
	//		else
	//			return true;
	//}
	if (!UKismetMathLibrary::InRange_FloatFloat(ScreemLocation.X, 450, 550))
	{
		//CLog::Print(GetRight);
		if (ScreemLocation.X < 450)
			if (GetRight < -0.1)
				return false;
			else
				return true;
		else if (ScreemLocation.X > 550)
			if (GetRight > 0.1)
				return false;
			else
				return true;
		//return UKismetMathLibrary::InRange_FloatFloat(ScreemLocation.X, 300, 700);

	}
	return true;
	//if (GetRight != 0)
	//	return false;
	//return true;
	//return true;
}

void ACCombatCharacter::OnCollision()
{
	//GetCap
	FollowCamera->PostProcessSettings.ColorGain = FVector4(1, 1, 1, 1);

}

void ACCombatCharacter::OnHuricain()
{
	StateManager->SetState(E_State::SpecialMagic);
	bCanMove = false;
	FActorSpawnParameters ActorSpawnParams;
	ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
	RetNull(HuricainClass);
	Huricain = GetWorld()->SpawnActor<ACHuricain>(HuricainClass, GetActorLocation(), GetActorRotation(), ActorSpawnParams);
	FollowCamera->PostProcessSettings.ColorGain = FVector4(1, 1, 2, 1);

}

void ACCombatCharacter::OffHuricain()
{
	StateManager->SetState(E_State::Idle);
	bCanMove = true;
	RetNull(HuricainClass);
	Huricain->Destroy();
	FollowCamera->PostProcessSettings.ColorGain = FVector4(1, 1, 1, 1);

}

void ACCombatCharacter::OnTargeting()
{
	DynamicTargeting->ToggleCameraLock();
}

void ACCombatCharacter::OnSpawnArrow()
{
	if (ArrowClass != NULL)
	{
		UWorld* const World = GetWorld();
		if (World != NULL)
		{
			const FRotator SpawnRotation = ArrowLocation->GetComponentRotation();// GetControlRotation();
			const FVector SpawnLocation = ArrowLocation->GetComponentLocation();// +FVector(100.0f, 0.0f, 10.0f);
			//((ArrowLocation != nullptr) ? 
			//ArrowLocation->GetComponentLocation() : GetActorLocation()) + SpawnRotation.RotateVector({ 100.0f, 0.0f, 10.0f });

			FTransform transform = FTransform::Identity;
			FActorSpawnParameters params;
			params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

			//params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
			RetNull(ArrowClass);
			if (!IsValid(Arrow))
			{
				//if(!Arrow->bShooting)
				Arrow = World->SpawnActor<ACArrow>(ArrowClass, SpawnLocation, SpawnRotation, params);
			}
			//Arrow = World->SpawnActor<ACArrow>(ArrowClass, transform, params);
		}
		//Arrow->Draw();

		//Arrow.AddUnique(Arrow);

	}

}

void ACCombatCharacter::OnGrabRope(ACRope* Rope)
{
	if (bGrabRope) return;
	MyRope = Rope;
	if (MyRope->bGarbed) return;
	MyRope->bGarbed = true;
	//CLog::Print(TEXT("OnGrabRope"));
	bGrabRope = true;
	StateManager->SetState(E_State::Grabing);
	bUseControllerRotationYaw = false;
	
	//AttachToComponent(MyRope->CableEnd, FAttachmentTransformRules(EAttachmentRule::KeepWorld, true));
	//GetCapsuleComponent()->SetupAttachment(MyRope->CableEnd);
	GetCapsuleComponent()->AttachToComponent(MyRope->GetCableEnd(),FAttachmentTransformRules(EAttachmentRule::KeepWorld, true), L"sword_use");
	FLatentActionInfo info = FLatentActionInfo();
	info.CallbackTarget = this;
	UKismetSystemLibrary::MoveComponentTo(GetCapsuleComponent(), FVector(0,0, -100 / MyRope->GetCableEnd()->GetComponentScale().Z), GetCapsuleComponent()->RelativeRotation, false, false, 0.5, true, EMoveComponentAction::Move, info);

	//GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ACCombatCharacter::OnUnGrabRope()
{
	ResetState();
	//OnJumping();
	bGrabRope = false;
	//DetachRootComponentFromParent(true);
	//GetCapsuleComponent()->DetachFromParent(true,true);
	GetCapsuleComponent()->DetachFromComponent(FDetachmentTransformRules(EDetachmentRule::KeepWorld, true));
	FLatentActionInfo info = FLatentActionInfo();
	info.CallbackTarget = this;
	FRotator rotation = GetControlRotation();
	//FRotator rotation = GetActorRotation();

	FRotator temp = FRotator(0, rotation.Yaw, 0);
	FVector forward = FQuat(temp).GetForwardVector();
	UKismetSystemLibrary::MoveComponentTo(GetCapsuleComponent(), GetActorLocation() + forward * 700, FRotator(0, UKismetMathLibrary::MakeRotFromX(GetActorForwardVector()).Yaw, 0), false, false, 0.5, true, EMoveComponentAction::Move, info);

	//GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

void ACCombatCharacter::enddash()
{
	bRuning = false;
}

void ACCombatCharacter::Setfallpoint()
{
	if (bcheckfalling) return;
	bcheckfalling = true;
	//CLog::Print(fallpoint.GetLocation().ToString());
	fallpoint = GetActorTransform();
}

void ACCombatCharacter::FallingReSpawn()
{
	if (FallRespawn == NULL) return;
	bcheckfalling = false;
	//SetActorTransform(fallpoint);
	FallRespawn->Spawn();
}

void ACCombatCharacter::TheWorld()
{
	if (!bstop)
	{
		UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 0.0f);
		bstop = true;
	}
	else
	{
		UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1.0f);
		bstop = false;
	}

}
