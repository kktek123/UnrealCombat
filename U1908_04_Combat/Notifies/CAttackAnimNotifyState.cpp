#include "CAttackAnimNotifyState.h"
#include "Global.h"
#include "CPlayer.h"
#include "CEnemy.h"

void UCAttackAnimNotifyState::NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);
	RetNull(MeshComp->GetOwner());

	if (MeshComp->GetOwner()->IsA(ACPlayer::StaticClass()))
	{
		ACPlayer* player = Cast<ACPlayer>(MeshComp->GetOwner());
		RetNull(player);

		player->BeginAttack();
		return;
	}
}

void UCAttackAnimNotifyState::NotifyTick(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float FrameDeltaTime)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime);

	
}

void UCAttackAnimNotifyState::NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	Super::NotifyEnd(MeshComp, Animation);
	RetNull(MeshComp->GetOwner());

	if (MeshComp->GetOwner()->IsA(ACPlayer::StaticClass()))
	{
		ACPlayer* player = Cast<ACPlayer>(MeshComp->GetOwner());
		RetNull(player);

		player->EndAttack();
		return;
	}

	if (MeshComp->GetOwner()->IsA(ACEnemy::StaticClass()))
	{
		ACEnemy* enemy = Cast<ACEnemy>(MeshComp->GetOwner());
		RetNull(enemy);

		enemy->EndAttack();
		return;
	}
}
