// Fill out your copyright notice in the Description page of Project Settings.


#include "CSwordParticle.h"
#include "Global.h"
#include "CCombatCharacter.h"
#include "CEnemy.h"
#include "Item/CSword.h"

void UCSwordParticle::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	//if (MeshComp->GetOwner()->IsA(ACPlayer::StaticClass()))



	if (MeshComp->GetOwner()->IsA(ACCombatCharacter::StaticClass()))
	{
		ACCombatCharacter* player = Cast<ACCombatCharacter>(MeshComp->GetOwner());
		RetNull(player);
		if (player->GetWeaponType() == E_WeaponType::Sword)
		{
			player->GetSword()->Gen_Particle();
		}
		return;
	}

	if (MeshComp->GetOwner()->IsA(ACEnemy::StaticClass()))
	{
		ACEnemy* enemy = Cast<ACEnemy>(MeshComp->GetOwner());
		RetNull(enemy);

		if (enemy->GetEnemyType() == E_EnemyType::Warrok)// && enemy->GetCombatType() == E_CombatType::Range)
		{
			enemy->OnJumping();
		}
		else
		{
			enemy->GetSword()->Gen_Particle();
		}
		return;
	}

}

