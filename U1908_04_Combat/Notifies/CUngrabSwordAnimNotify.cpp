#include "CUngrabSwordAnimNotify.h"
#include "Global.h"
#include "CPlayer.h"
#include "Item/CSword.h"

void UCUngrabSwordAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	//if (MeshComp->GetOwner()->IsA(ACPlayer::StaticClass()))
	ACPlayer* player = Cast<ACPlayer>(MeshComp->GetOwner());
	RetNull(player);

	player->GetSword()->AttachToComponent(MeshComp, FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), "WeaponHolsterSocket");
}
