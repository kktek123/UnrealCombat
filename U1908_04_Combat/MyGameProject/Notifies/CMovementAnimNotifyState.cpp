// Fill out your copyright notice in the Description page of Project Settings.


#include "CMovementAnimNotifyState.h"
#include "Global.h"
#include "CCombatCharacter.h"
#include "Item/CSword.h"

void UCMovementAnimNotifyState::NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	ACCombatCharacter* player = Cast<ACCombatCharacter>(MeshComp->GetOwner());
	RetNull(player);

}

void UCMovementAnimNotifyState::NotifyTick(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float FrameDeltaTime)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime);


}

void UCMovementAnimNotifyState::NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	ACCombatCharacter* player = Cast<ACCombatCharacter>(MeshComp->GetOwner());
	RetNull(player);
	player->ResetState();
}

