#include "CPlayerAnimInstance.h"
#include "Global.h"
#include "CPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"

UCPlayerAnimInstance::UCPlayerAnimInstance()
{

}

void UCPlayerAnimInstance::NativeBeginPlay()
{
	Player = Cast<ACPlayer>(TryGetPawnOwner());

	UActorComponent* actorComp = Player->GetComponentByClass(UCInverseKinemetics::StaticClass());
	if (actorComp != NULL)
		Foot = Cast<UCInverseKinemetics>(actorComp);
}

void UCPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	RetNull(Player);

	Speed = Player->GetVelocity().Size();
	bInAir = Player->GetCharacterMovement()->IsFalling();
	bDrawing = Player->GetDrawing();
	bSheathing = Player->GetSheathing();
	Direction = CalculateDirection(Player->GetVelocity(), Player->GetActorRotation());
	Effector = Foot->GetEffector();
}
