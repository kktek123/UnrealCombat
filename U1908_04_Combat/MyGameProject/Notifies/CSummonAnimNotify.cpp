// Fill out your copyright notice in the Description page of Project Settings.


#include "CSummonAnimNotify.h"
#include "Global.h"
#include "CCombatCharacter.h"
#include "CEnemy.h"

void UCSummonAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	RetNull(MeshComp->GetOwner());
	//player->offbl
	if (MeshComp->GetOwner()->IsA(ACEnemy::StaticClass()))
	{
		ACEnemy* enemy = Cast<ACEnemy>(MeshComp->GetOwner());
		RetNull(enemy);

		enemy->SummonEnemy();
		return;
	}
}

