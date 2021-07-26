// Fill out your copyright notice in the Description page of Project Settings.


#include "CEquippedOneHandSwordAnimNotify.h"
#include "Global.h"
#include "CCombatCharacter.h"
#include "Item/CSword.h"

void UCEquippedOneHandSwordAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	if (MeshComp->GetOwner()->IsA(ACCombatCharacter::StaticClass()))
	{
		ACCombatCharacter* combatplayer = Cast<ACCombatCharacter>(MeshComp->GetOwner());
		RetNull(combatplayer);
		//combatplayer->GetAttackCount();
	}

	//combatplayer->Equipped();
}
