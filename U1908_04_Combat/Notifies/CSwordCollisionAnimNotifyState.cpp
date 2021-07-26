#include "CSwordCollisionAnimNotifyState.h"
#include "Global.h"
#include "CPlayer.h"
#include "Item/CSword.h"

void UCSwordCollisionAnimNotifyState::NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	ACPlayer* player = Cast<ACPlayer>(MeshComp->GetOwner());
	RetNull(player);

	player->GetSword()->GetCapsule()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

void UCSwordCollisionAnimNotifyState::NotifyTick(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float FrameDeltaTime)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime);

	
}

void UCSwordCollisionAnimNotifyState::NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	ACPlayer* player = Cast<ACPlayer>(MeshComp->GetOwner());
	RetNull(player);

	player->GetSword()->GetCapsule()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}
