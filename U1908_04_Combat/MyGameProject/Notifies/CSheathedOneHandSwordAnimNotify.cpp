// Fill out your copyright notice in the Description page of Project Settings.


#include "CSheathedOneHandSwordAnimNotify.h"
#include "Global.h"
#include "CCombatCharacter.h"
#include "Item/CSword.h"

void UCSheathedOneHandSwordAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	ACCombatCharacter* player = Cast<ACCombatCharacter>(MeshComp->GetOwner());
	RetNull(player);
	//if (MeshComp->GetOwner()->IsA(ACCombatCharacter::StaticClass()))
	//{
	//	return;
	//}

}

