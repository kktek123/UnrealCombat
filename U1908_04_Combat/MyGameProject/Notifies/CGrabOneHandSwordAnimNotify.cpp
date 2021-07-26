// Fill out your copyright notice in the Description page of Project Settings.


#include "CGrabOneHandSwordAnimNotify.h"
#include "Global.h"
#include "CCombatCharacter.h"
#include "Item/CSword.h"

void UCGrabOneHandSwordAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	//if (MeshComp->GetOwner()->IsA(ACPlayer::StaticClass()))
	//if (MeshComp->GetOwner()->IsA(ACCombatCharacter::StaticClass()))
	//{
	//	
	//	return;
	//}
	ACCombatCharacter* player = Cast<ACCombatCharacter>(MeshComp->GetOwner());
	RetNull(player);

	if (player->GetWeaponType() == E_WeaponType::Sword)
		player->GetSword()->AttachToComponent(MeshComp, FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), "sword_use");
	else if (player->GetWeaponType() == E_WeaponType::Bow)
		player->GetSword()->AttachToComponent(MeshComp, FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), "bow_use");
	else if (player->GetWeaponType() == E_WeaponType::Spell)
		player->GetSword()->ChangeSpell();

	player->Equipped();

}

