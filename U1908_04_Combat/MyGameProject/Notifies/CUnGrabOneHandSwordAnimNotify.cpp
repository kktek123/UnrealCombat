// Fill out your copyright notice in the Description page of Project Settings.


#include "CUnGrabOneHandSwordAnimNotify.h"
#include "Global.h"
#include "CCombatCharacter.h"
#include "Item/CSword.h"

void UCUnGrabOneHandSwordAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	ACCombatCharacter* player = Cast<ACCombatCharacter>(MeshComp->GetOwner());
	RetNull(player);

	if (player->GetWeaponType() == E_WeaponType::Sword)
		player->GetSword()->AttachToComponent(MeshComp, FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), "sword");
	if (player->GetWeaponType() == E_WeaponType::Bow)
		player->GetSword()->AttachToComponent(MeshComp, FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), "bow");
	if (player->GetWeaponType() == E_WeaponType::Spell)
		player->GetSword()->ChangeSpell();

	player->Sheathed();


}

