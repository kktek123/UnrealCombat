#include "CCombatAnimInstance.h"
#include "Global.h"
#include "CCombatCharacter.h"
#include "CCStateManager.h"
#include "Kismet/GameplayStatics.h"
#include "Math/UnrealMathUtility.h"
#include "GameFramework/CharacterMovementComponent.h"

UCCombatAnimInstance::UCCombatAnimInstance()
{

}

void UCCombatAnimInstance::NativeBeginPlay()
{
	CombatPlayer = Cast<ACCombatCharacter>(TryGetPawnOwner());
	UActorComponent* actorComp = CombatPlayer->GetComponentByClass(UCInverseKinemetics::StaticClass());
	if (actorComp != NULL)
		Foot = Cast<UCInverseKinemetics>(actorComp);
}

void UCCombatAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	RetNull(CombatPlayer);


	Speed = CombatPlayer->GetVelocity().Size();
	bInAir = CombatPlayer->GetCharacterMovement()->IsFalling();
	Direction = CalculateDirection(CombatPlayer->GetVelocity(), CombatPlayer->GetActorRotation());
	Effector = Foot->GetEffector();

	//LocomotionRateScale

	bDrawing = CombatPlayer->GetDrawing();
	bSheathing = CombatPlayer->GetSheathing();
	state = CombatPlayer->GetStateManager()->GetState();
	combatType = CombatPlayer->GetCombatType();
	weaponType = CombatPlayer->GetWeaponType();
	activity = CombatPlayer->GetStateManager()->GetActivityValue(E_Activity::IsBlockingPressed);
	bShieldEquipped = CombatPlayer->GetShieldEquipped();
	BlockAlpha = CombatPlayer->GetBlockAlpha();
	AimAlpha = CombatPlayer->GetAimAlpha();
	bGrabRope = CombatPlayer->GetGrabRope();
	//if(IsValid(UGameplayStatics::GetPlayerController(this,0)))
	//{
	//}
	float Y = 0;
	UGameplayStatics::GetPlayerController(this, 0)->GetInputMouseDelta(MouseDeltaX, Y);
	if (CombatPlayer->GetStateManager()->GetActivityValue(E_Activity::IsAimingPressed))
		IsLookingForward = true;
	else
		IsLookingForward = false;

	UpdateLeanAmount();
	UpdateLookAtValues();
	UpdateAimOffset();
	
}

void UCCombatAnimInstance::UpdateLeanAmount()
{
	LeanAmount = FMath::FInterpTo(AimOffsetAlpha, 0, 10, 5.0f);

}

void UCCombatAnimInstance::UpdateLookAtValues()
{
	FRotator current = UKismetMathLibrary::MakeRotator(0, LookatPitch, LookatYaw);
	FRotator ControlRotate = CombatPlayer->GetControlRotation();
	//ControlRotate.Yaw += 30;
	//ControlRotate.Pitch -= 10;
	FRotator Target = UKismetMathLibrary::NormalizedDeltaRotator(ControlRotate,CombatPlayer->GetActorRotation());
	//AimOffsetAlpha = FMath::FInterpTo(AimOffsetAlpha, IsLookingForward, this->GetWorld->UWorld::GetDeltaSeconds(), 5.0f);
	FRotator BreakRotator = FMath::RInterpTo(current, Target, UGameplayStatics::GetWorldDeltaSeconds(this),15.0f);

	LookatPitch = UKismetMathLibrary::ClampAngle(BreakRotator.Pitch, -90, 90);
	LookatYaw = UKismetMathLibrary::ClampAngle(BreakRotator.Yaw, -90, 90);

}

void UCCombatAnimInstance::UpdateAimOffset()
{
	AimOffsetAlpha = FMath::FInterpTo(AimOffsetAlpha, IsLookingForward, UGameplayStatics::GetWorldDeltaSeconds(this), 1.0f);
}


