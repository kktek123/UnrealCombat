// Fill out your copyright notice in the Description page of Project Settings.


#include "CHitCollisionAnimNotifyState.h"
#include "Global.h"
#include "CCombatCharacter.h"
#include "CEnemy.h"
#include "Item/CSword.h"
#include "MyGameProject/Item/CDisplayedItem.h"


void UCHitCollisionAnimNotifyState::NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);
	RetNull(MeshComp->GetOwner());
	if (MeshComp->GetOwner()->IsA(ACCombatCharacter::StaticClass()))
	{
		ACCombatCharacter* player = Cast<ACCombatCharacter>(MeshComp->GetOwner());
		RetNull(player);
		//CLog::Print(TEXT("OnCollision"));
		player->GetSword()->GetCapsule()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		player->OnSwing();
		return;
	}

	if (MeshComp->GetOwner()->IsA(ACEnemy::StaticClass()))
	{
		ACEnemy* enemy = Cast<ACEnemy>(MeshComp->GetOwner());
		RetNull(enemy);
		//CLog::Print(TEXT("OnCollision"));
		enemy->GetSword()->GetCapsule()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		//enemy->AttackCheck();
		return;
	}


}

void UCHitCollisionAnimNotifyState::NotifyTick(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float FrameDeltaTime)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime);


}

void UCHitCollisionAnimNotifyState::NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	Super::NotifyEnd(MeshComp, Animation);
	RetNull(MeshComp->GetOwner());
	ACCombatCharacter* player = Cast<ACCombatCharacter>(MeshComp->GetOwner());


	if (MeshComp->GetOwner()->IsA(ACCombatCharacter::StaticClass()))
	{
		ACCombatCharacter* player = Cast<ACCombatCharacter>(MeshComp->GetOwner());
		RetNull(player);
		//CLog::Print(TEXT("OffCollision"));
		player->GetSword()->GetCapsule()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		return;
	}

	if (MeshComp->GetOwner()->IsA(ACEnemy::StaticClass()))
	{
		//CLog::Print(TEXT("OffCollision"));

		ACEnemy* enemy = Cast<ACEnemy>(MeshComp->GetOwner());
		RetNull(enemy);

		enemy->GetSword()->GetCapsule()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		return;
	}

}
