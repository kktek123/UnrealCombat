// Fill out your copyright notice in the Description page of Project Settings.


#include "CMagicBoomAnimNotifyState.h"
#include "Global.h"
#include "CCombatCharacter.h"
#include "CEnemy.h"

void UCMagicBoomAnimNotifyState::NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);
	RetNull(MeshComp->GetOwner());


	//if (MeshComp->GetOwner()->IsA(ACCombatCharacter::StaticClass()))
	//{
	//	ACCombatCharacter* player = Cast<ACCombatCharacter>(MeshComp->GetOwner());
	//	RetNull(player);

	//	player->BeginAttack();
	//	return;
	//}


	if (MeshComp->GetOwner()->IsA(ACEnemy::StaticClass()))
	{
		ACEnemy* enemy = Cast<ACEnemy>(MeshComp->GetOwner());
		RetNull(enemy);

		enemy->MagicBoom();
		return;
	}
}

void UCMagicBoomAnimNotifyState::NotifyTick(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float FrameDeltaTime)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime);
}

void UCMagicBoomAnimNotifyState::NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	Super::NotifyEnd(MeshComp, Animation);
	RetNull(MeshComp->GetOwner());

	//if (MeshComp->GetOwner()->IsA(ACCombatCharacter::StaticClass()))
	//{
	//	ACCombatCharacter* player = Cast<ACCombatCharacter>(MeshComp->GetOwner());
	//	RetNull(player);

	//	player->EndAttack();
	//	return;
	//}

	//if (MeshComp->GetOwner()->IsA(ACEnemy::StaticClass()))
	//{
	//	ACEnemy* enemy = Cast<ACEnemy>(MeshComp->GetOwner());
	//	RetNull(enemy);

	//	enemy->EndAttack();
	//	return;
	//}
}

