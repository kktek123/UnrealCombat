// Fill out your copyright notice in the Description page of Project Settings.


#include "CResetCount.h"
#include "Global.h"
#include "CCombatCharacter.h"
#include "CEnemy.h"

void UCResetCount::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	if (MeshComp->GetOwner()->IsA(ACCombatCharacter::StaticClass()))
	{
		ACCombatCharacter* player = Cast<ACCombatCharacter>(MeshComp->GetOwner());
		RetNull(player);

		player->ResetState();
		return;
	}

	if (MeshComp->GetOwner()->IsA(ACEnemy::StaticClass()))
	{
		ACEnemy* enemy = Cast<ACEnemy>(MeshComp->GetOwner());
		RetNull(enemy);
		//CLog::Print(TEXT("OnCollision"));
		enemy->ResetState();
		//enemy->AttackCheck();
		return;
	}


	//cmbatplayer->Equipped();
	
}

