// Fill out your copyright notice in the Description page of Project Settings.


#include "CDI_Spell.h"
#include "CCombatCharacter.h"
#include "Global.h"

ADI_Spell::ADI_Spell(const class FObjectInitializer& ObjectInitializer)
{
	Magic= ObjectInitializer.CreateDefaultSubobject<USphereComponent>(this, TEXT("magic"));
	RootComponent = Magic;

	Fireball = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Fireball"));
	Fireball->SetupAttachment(Magic);
	Fireball->SetHiddenInGame(true);

	Heal = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Heal"));
	Heal->SetupAttachment(Magic);
	Heal->SetHiddenInGame(true);

	Storm = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Storm"));
	Storm->SetupAttachment(Magic);
	Storm->SetHiddenInGame(true);

	Boom = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Boom"));
	Boom->SetupAttachment(Magic);
	Boom->SetHiddenInGame(true);
																	 
	Burf = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Burf"));
	Burf->SetupAttachment(Magic);
	Burf->SetHiddenInGame(true);

	FString path = L"ParticleSystem'/Game/DynamicCombatSystem/VFX/P_FireHand.P_FireHand'";
	ConstructorHelpers::FObjectFinder<UParticleSystem> fireball(*path);
	if (fireball.Succeeded())
		Fireball->SetTemplate(fireball.Object);

	path = L"ParticleSystem'/Game/DynamicCombatSystem/VFX/P_HealingHand.P_HealingHand'";
	ConstructorHelpers::FObjectFinder<UParticleSystem> heal(*path);
	if (heal.Succeeded())
		Heal->SetTemplate(heal.Object);

	path = L"ParticleSystem'/Game/DynamicCombatSystem/VFX/P_WindHand.P_WindHand'";
	ConstructorHelpers::FObjectFinder<UParticleSystem> storm(*path);
	if (storm.Succeeded())
		Storm->SetTemplate(storm.Object);

	path = L"ParticleSystem'/Game/DynamicCombatSystem/VFX/P_BloodHand.P_BloodHand'";
	ConstructorHelpers::FObjectFinder<UParticleSystem> boom(*path);
	if (boom.Succeeded())
		Boom->SetTemplate(boom.Object);

	path = L"ParticleSystem'/Game/DynamicCombatSystem/VFX/P_ArcaneHand.P_ArcaneHand'";
	ConstructorHelpers::FObjectFinder<UParticleSystem> burf(*path);
	if (burf.Succeeded())
		Burf->SetTemplate(burf.Object);


	weaponType = E_WeaponType::Spell;
}

void ACDisplayedItem::ChangeSpell()
{
	if (MyPawn->GetState() == E_State::Drawing && MyPawn->GetWeaponType() == E_WeaponType::Spell)
	{
		if (MyPawn->GetMagicType() == E_MagicType::Fireball)
			Fireball->SetHiddenInGame(false);
		else
			Fireball->SetHiddenInGame(true);

		if (MyPawn->GetMagicType() == E_MagicType::Heal)
			Heal->SetHiddenInGame(false);
		else
			Heal->SetHiddenInGame(true);

		if (MyPawn->GetMagicType() == E_MagicType::Strom)
			Storm->SetHiddenInGame(false);
		else
			Storm->SetHiddenInGame(true);

		if (MyPawn->GetMagicType() == E_MagicType::Boom)
			Boom->SetHiddenInGame(false);
		else
			Boom->SetHiddenInGame(true);

		if (MyPawn->GetMagicType() == E_MagicType::Burf)
			Burf->SetHiddenInGame(false);
		else
			Burf->SetHiddenInGame(true);
	}
	else
	{
		Fireball->SetHiddenInGame(true);
		Heal->SetHiddenInGame(true);
		Storm->SetHiddenInGame(true);
		Boom->SetHiddenInGame(true);
		Burf->SetHiddenInGame(true);
	}
}
void ACDisplayedItem::UnCastSpell()
{
	Fireball->SetHiddenInGame(true);
	Heal->SetHiddenInGame(true);
	Storm->SetHiddenInGame(true);
	Boom->SetHiddenInGame(true);
	Burf->SetHiddenInGame(true);
}


void ACDisplayedItem::CastSpell()
{
	if (MyPawn->GetWeaponType() == E_WeaponType::Spell)
	{
		if (MyPawn->GetMagicType() == E_MagicType::Fireball)
			Fireball->SetHiddenInGame(false);
		else
			Fireball->SetHiddenInGame(true);

		if (MyPawn->GetMagicType() == E_MagicType::Heal)
			Heal->SetHiddenInGame(false);
		else
			Heal->SetHiddenInGame(true);

		if (MyPawn->GetMagicType() == E_MagicType::Strom)
			Storm->SetHiddenInGame(false);
		else
			Storm->SetHiddenInGame(true);

		if (MyPawn->GetMagicType() == E_MagicType::Boom)
			Boom->SetHiddenInGame(false);
		else
			Boom->SetHiddenInGame(true);

		if (MyPawn->GetMagicType() == E_MagicType::Burf)
			Burf->SetHiddenInGame(false);
		else
			Burf->SetHiddenInGame(true);
	}
}
