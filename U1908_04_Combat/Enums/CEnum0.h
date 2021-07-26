// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CEnum0.generated.h"

UENUM(BlueprintType)
enum class E_ActivityEndResult : uint8
{
	Finished UMETA(DisplayName = "Finished"),
	Interrupted UMETA(DisplayName = "Interrupted"),
	Canceled UMETA(DisplayName = "Canceled"),
	OutOfMana UMETA(DisplayName = "OutOfMana"),
	Destroyed UMETA(DisplayName = "Destroyed"),
};

UENUM(BlueprintType)
enum class E_Activity : uint8
{
	None UMETA(DisplayName = "None"),
	IsBlockingPressed UMETA(DisplayName = "IsBlockingPressed"),
	IsAimingPressed UMETA(DisplayName = "IsAimingPressed"),
	IsImmortal UMETA(DisplayName = "IsImmortal"),
	CantBeInterrupted UMETA(DisplayName = "CantBeInterrupted"),
	IsLookingForward UMETA(DisplayName = "IsLookingForward"),
	CanParryHit UMETA(DisplayName = "CanParryHit"),
	IsZooming UMETA(DisplayName = "IsZooming"),
};

UENUM(BlueprintType)
enum class EC_AIBehavior : uint8
{
	Idle UMETA(DisplayName = "Idle"),
	Patrol UMETA(DisplayName = "Patrol"),
	MeleeAttack UMETA(DisplayName = "MeleeAttack"),
	RangeAttack UMETA(DisplayName = "RangeAttack"),
	MagicAttack UMETA(DisplayName = "MagicAttack"),
	Approach UMETA(DisplayName = "Approach"),
	Flee UMETA(DisplayName = "Flee"),
	StrafeAround UMETA(DisplayName = "StrafeAround"),
	Hit UMETA(DisplayName = "Hit"),
	Summon UMETA(DisplayName = "Summon"),
	Heal UMETA(DisplayName = "Heal"),
};

UENUM(BlueprintType)
enum class E_ApplyEffectMethod : uint8
{
	Stack UMETA(DisplayName = "Stack"),
	Replace UMETA(DisplayName = "Replace"),
};

UENUM(BlueprintType)
enum class E_AttackResult : uint8
{
	Success UMETA(DisplayName = "Success"),
	Failed UMETA(DisplayName = "Failed"),
	Blocked UMETA(DisplayName = "Blocked"),
	Parried UMETA(DisplayName = "Parried"),
};

UENUM(BlueprintType)
enum class E_CollisionPart : uint8
{
	None UMETA(DisplayName = "None"),
	MainHandItem UMETA(DisplayName = "MainHandItem"),
	RightHand UMETA(DisplayName = "RightHand"),
	LeftHand UMETA(DisplayName = "LeftHand"),
	RightFoot UMETA(DisplayName = "RightFoot"),
	LeftFoot UMETA(DisplayName = "LeftFoot"),
};

UENUM(BlueprintType)
enum class E_CombatType : uint8
{
	Unarmed UMETA(DisplayName = "Unarmed"),
	Melee UMETA(DisplayName = "Melee"),
	Range UMETA(DisplayName = "Range"),
	Magic UMETA(DisplayName = "Magic"),
	Summon UMETA(DisplayName = "Summon"),
};

UENUM(BlueprintType)
enum class E_Direction : uint8
{
	Front UMETA(DisplayName = "Front"),
	Back UMETA(DisplayName = "Back"),
	Left UMETA(DisplayName = "Left"),
	Right UMETA(DisplayName = "Right"),
};

UENUM(BlueprintType)
enum class E_EffectType : uint8
{
	None UMETA(DisplayName = "None"),
	Stun UMETA(DisplayName = "Stun"),
	Knockdown UMETA(DisplayName = "Knockdown"),
	Burning UMETA(DisplayName = "Burning"),
	Backstab UMETA(DisplayName = "Backstab"),
	Impact UMETA(DisplayName = "Impact"),
	Parried UMETA(DisplayName = "Parried"),

};

UENUM(BlueprintType)
enum class E_HandleSameItemMethod : uint8
{
	Unequip UMETA(DisplayName = "Unequip"),
	Update UMETA(DisplayName = "Update"),
};

UENUM(BlueprintType)
enum class E_InputBufferKey: uint8
{
	None UMETA(DisplayName = "None"),
	LightAttack UMETA(DisplayName = "LightAttack"),
	HeavyAttack UMETA(DisplayName = "HeavyAttack"),
	ThrustAttack UMETA(DisplayName = "ThrustAttack"),
	SpecialAttack UMETA(DisplayName = "SpecialAttack"),
	FallingAttack UMETA(DisplayName = "FallingAttack"),
	Roll UMETA(DisplayName = "Roll"),
	Jump UMETA(DisplayName = "Jump"),
	Parry UMETA(DisplayName = "Parry"),
	ToggleCombat UMETA(DisplayName = "ToggleCombat"),
	SwitchMainHandTypeUp UMETA(DisplayName = "SwitchMainHandTypeUp"),
	SwitchMainHandTypeDown UMETA(DisplayName = "SwitchMainHandTypeDown"),
	SwitchMainHandItemUp UMETA(DisplayName = "SwitchMainHandItemUp"),
	SwitchMainHandItemDown UMETA(DisplayName = "SwitchMainHandItemDown"),
	AbilityAttack UMETA(DisplayName = "AbilityAttack"),
	SetSpellActiveIndex UMETA(DisplayName = "SetSpellActiveIndex"),

};

UENUM(BlueprintType)
enum class E_ItemType : uint8
{
	None UMETA(DisplayName = "None"),
	Spell UMETA(DisplayName = "Spell"),
	Heavy UMETA(DisplayName = "Heavy"),
	Shield UMETA(DisplayName = "Shield"),
	Head UMETA(DisplayName = "Head"),
	Top UMETA(DisplayName = "Top"),
	Legs UMETA(DisplayName = "Legs"),
	Hands UMETA(DisplayName = "Hands"),
	Feet UMETA(DisplayName = "Feet"),
	Arrows UMETA(DisplayName = "Arrows"),
	Tool UMETA(DisplayName = "Tool"),
	Material UMETA(DisplayName = "Material"),
	Ring UMETA(DisplayName = "Ring"),
	MeleeWeapon UMETA(DisplayName = "MeleeWeapon"),
	RangeWeapon UMETA(DisplayName = "RangeWeapon"),
	Necklace UMETA(DisplayName = "Necklace"),

};

UENUM(BlueprintType)
enum class E_MeleeAttackType : uint8
{
	None UMETA(DisplayName = "None"),
	Light UMETA(DisplayName = "Light"),
	Heavy UMETA(DisplayName = "Heavy"),
	Special UMETA(DisplayName = "Special"),
	Thrust UMETA(DisplayName = "Thrust"),
	Falling UMETA(DisplayName = "Falling"),

};

UENUM(BlueprintType)
enum class E_MontageAction: uint8
{
	None UMETA(DisplayName = "None"),
	LightAttack UMETA(DisplayName = "LightAttack"),
	HeavyAttack UMETA(DisplayName = "HeavyAttack"),
	ThrustAttack UMETA(DisplayName = "ThrustAttack"),
	SpecialAttack UMETA(DisplayName = "SpecialAttack"),
	FallingAttack UMETA(DisplayName = "FallingAttack"),
	RollForward UMETA(DisplayName = "RollForward"),
	RollLeft UMETA(DisplayName = "RollLeft"),
	RollRight UMETA(DisplayName = "RollRight"),
	RollBackward UMETA(DisplayName = "RollBackward"),
	DrawWeapon UMETA(DisplayName = "DrawWeapon"),
	DisarmWeapon UMETA(DisplayName = "DisarmWeapon"),
	StunFront UMETA(DisplayName = "StunFront"),
	StunBack UMETA(DisplayName = "StunBack"),
	StunRight UMETA(DisplayName = "StunRight"),
	StunLeft UMETA(DisplayName = "StunLeft"),
	Impact UMETA(DisplayName = "Impact"),
	Block UMETA(DisplayName = "Block"),
	Parry UMETA(DisplayName = "Parry"),
	Parried UMETA(DisplayName = "Parried"),
	Backstabbed UMETA(DisplayName = "Backstabbed"),
	Backstab UMETA(DisplayName = "Backstab"),
	ShootArrow UMETA(DisplayName = "ShootArrow"),

};

UENUM(BlueprintType)
enum class E_MovementState : uint8
{
	Idle UMETA(DisplayName = "Idle"),
	Walk UMETA(DisplayName = "Walk"),
	Jog UMETA(DisplayName = "Jog"),
	Sprint UMETA(DisplayName = "Sprint"),
};

UENUM(BlueprintType)
enum class E_State : uint8
{
	Idle UMETA(DisplayName = "Idle"),
	Disabled UMETA(DisplayName = "Disabled"),
	Attacking UMETA(DisplayName = "Attacking"),
	Rolling UMETA(DisplayName = "Rolling"),
	Falling UMETA(DisplayName = "Falling"),
	Interacting UMETA(DisplayName = "Interacting"),
	Backstabbing UMETA(DisplayName = "Backstabbing"),
	Parrying UMETA(DisplayName = "Parrying"),
	Dead UMETA(DisplayName = "Dead"),
	Blocking UMETA(DisplayName = "Blocking"),
	Drawing UMETA(DisplayName = "Drawing"),
	Sheathing UMETA(DisplayName = "Sheathing"),
	Aiming UMETA(DisplayName = "Aiming"),
	Damage UMETA(DisplayName = "Damage"),
	Stun UMETA(DisplayName = "Stun"),
	SpecialMagic UMETA(DisplayName = "SpecialMagic"),
	Grabing UMETA(DisplayName = "Grabing"),
};

UENUM(BlueprintType)
enum class E_StatType : uint8
{
	None UMETA(DisplayName = "None"),
	Health UMETA(DisplayName = "Health"),
	Stamina UMETA(DisplayName = "Stamina"),
	Mana UMETA(DisplayName = "Mana"),
	Damage UMETA(DisplayName = "Damage"),
	Armor UMETA(DisplayName = "Armor"),
	CritMultiplier UMETA(DisplayName = "CritMultiplier"),
	AttackSpeed UMETA(DisplayName = "AttackSpeed"),
	Block UMETA(DisplayName = "Block"),
	MeleeAttackStaminaCost UMETA(DisplayName = "MeleeAttackStaminaCost"),
	MagicDamage UMETA(DisplayName = "MagicDamage"),
	CastingSpeed UMETA(DisplayName = "CastingSpeed"),

};

UENUM(BlueprintType)
enum class E_WeaponType : uint8
{
	None UMETA(DisplayName = "None"),
	Sword UMETA(DisplayName = "Sword"),
	Axe UMETA(DisplayName = "Axe"),
	Bow UMETA(DisplayName = "Bow"),
	Spell UMETA(DisplayName = "Spell"),
	Shield UMETA(DisplayName = "Shield"),
};

UENUM(BlueprintType)
enum class E_MagicType : uint8
{
	Fireball UMETA(DisplayName = "Fireball"),
	Heal UMETA(DisplayName = "Heal"),
	Strom UMETA(DisplayName = "Strom"),
	Boom UMETA(DisplayName = "Boom"),
	Burf UMETA(DisplayName = "Burf"),
	Shield UMETA(DisplayName = "Shield"),
};

UENUM(BlueprintType)
enum class E_CameraSide : uint8
{
	UpSide UMETA(DisplayName = "UpSide"),
	RightSide UMETA(DisplayName = "RightSide"),
	FrontSide UMETA(DisplayName = "FrontSide"),
};

UENUM(BlueprintType)
enum class E_RotationMode : uint8
{
	FaceCamera UMETA(DisplayName = "FaceCamera"),
	OrientToMovement UMETA(DisplayName = "OrientToMovement"),
};
UCLASS()
class U1908_04_COMBAT_API ACEnum0 : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACEnum0();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
