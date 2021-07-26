// Fill out your copyright notice in the Description page of Project Settings.


#include "CMagicParticle.h"
#include "Global.h"
#include "CCombatCharacter.h"
#include "CEnemy.h"

void UCMagicParticle::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	//if (MeshComp->GetOwner()->IsA(ACPlayer::StaticClass()))



	//if (MeshComp->GetOwner()->IsA(ACCombatCharacter::StaticClass()))
	//{
	//	ACCombatCharacter* player = Cast<ACCombatCharacter>(MeshComp->GetOwner());
	//	RetNull(player);
	//	if (player->GetWeaponType() == E_WeaponType::Sword)
	//	{
	//		player->GetSword()->Gen_Particle();
	//	}
	//	return;
	//}

	if (MeshComp->GetOwner()->IsA(ACEnemy::StaticClass()))
	{
		ACEnemy* enemy = Cast<ACEnemy>(MeshComp->GetOwner());
		RetNull(enemy);

		enemy->OnMagic();
		//if (enemy->GetEnemyType() == E_EnemyType::Warrok)// && enemy->GetCombatType() == E_CombatType::Range)
		//{
		//	enemy->OnJumping();
		//}
		//else
		//{
		//	enemy->GetSword()->Gen_Particle();
		//}
		return;
	}

}


