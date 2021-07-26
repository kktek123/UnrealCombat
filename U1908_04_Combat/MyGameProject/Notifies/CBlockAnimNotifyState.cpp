// Fill out your copyright notice in the Description page of Project Settings.


#include "CBlockAnimNotifyState.h"
#include "Global.h"
#include "CCombatCharacter.h"

void UCBlockAnimNotifyState::NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);
	RetNull(MeshComp->GetOwner());


	if (MeshComp->GetOwner()->IsA(ACCombatCharacter::StaticClass()))
	{
		ACCombatCharacter* player = Cast<ACCombatCharacter>(MeshComp->GetOwner());
		RetNull(player);

		player->BeginBlock();
		return;
	}

}

void UCBlockAnimNotifyState::NotifyTick(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float FrameDeltaTime)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime);
}

void UCBlockAnimNotifyState::NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	Super::NotifyEnd(MeshComp, Animation);
	RetNull(MeshComp->GetOwner());

	if (MeshComp->GetOwner()->IsA(ACCombatCharacter::StaticClass()))
	{
		ACCombatCharacter* player = Cast<ACCombatCharacter>(MeshComp->GetOwner());
		RetNull(player);

		player->EndBlock();
		return;
	}
}
