// Fill out your copyright notice in the Description page of Project Settings.


#include "CShootArrowAnimNotify.h"
#include "Global.h"
#include "CCombatCharacter.h"
#include "CEnemy.h"
#include "MyGameProject/Item/CArrow.h"
#include "CCStateManager.h"

void UCShootArrowAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	//RetNull(Arrow);
	//Arrow->Shoot();
	//cmbatplayer->Equipped();
	if (MeshComp->GetOwner()->IsA(ACCombatCharacter::StaticClass()))
	{
		ACCombatCharacter* combatplayer = Cast<ACCombatCharacter>(MeshComp->GetOwner());

		RetNull(combatplayer);
		combatplayer->OnShoot();
		combatplayer->GetStateManager()->SetActivity(E_Activity::IsAimingPressed, false);
		return;
	}

	if (MeshComp->GetOwner()->IsA(ACEnemy::StaticClass()))
	{
		ACEnemy* enemy = Cast<ACEnemy>(MeshComp->GetOwner());
		RetNull(enemy);
		enemy->OffAiming();
		//enemy->ResetState();
		//enemy->AttackCheck();
		return;
	}


}

