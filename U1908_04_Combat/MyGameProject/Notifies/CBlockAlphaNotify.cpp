// Fill out your copyright notice in the Description page of Project Settings.


#include "CBlockAlphaNotify.h"
#include "Global.h"
#include "CCombatCharacter.h"
#include "Item/CSword.h"

void UCBlockAlphaNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	ACCombatCharacter* player = Cast<ACCombatCharacter>(MeshComp->GetOwner());
	RetNull(player);
	//player->offbl

}
