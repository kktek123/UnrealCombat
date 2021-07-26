#include "CEnemyAnimInstance.h"
#include "Global.h"
#include "CEnemy.h"
#include "CCStateManager.h"

UCEnemyAnimInstance::UCEnemyAnimInstance()
{

}

void UCEnemyAnimInstance::NativeBeginPlay()
{
	Enemy = Cast<ACEnemy>(TryGetPawnOwner());
}

void UCEnemyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	RetNull(Enemy);

	Speed = Enemy->GetVelocity().Size();
	Direction = CalculateDirection(Enemy->GetVelocity(), Enemy->GetActorRotation());
	State = Enemy->GetStateManager()->GetState();
	Blocking = Enemy->GetBlocking();
	EnemyType = Enemy->GetEnemyType();
	AimAlpha = Enemy->GetAimAlpha();
}

