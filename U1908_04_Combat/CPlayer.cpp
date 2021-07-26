#include "CPlayer.h"
#include "Global.h"
#include "Item/CSword.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Perception/AIPerceptionSystem.h"
#include "Perception/AISense_Sight.h"

ACPlayer::ACPlayer()
{
	PrimaryActorTick.bCanEverTick = true;
	
	bUseControllerRotationYaw = false;
	
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->MaxWalkSpeed = 400.0f;


	FString path = L"Blueprint'/Game/Item/BpCSword.BpCSword_C'";
	ConstructorHelpers::FClassFinder<ACSword> sword(*path);
	if (sword.Succeeded())
		SwordClass = sword.Class;

	path = L"AnimMontage'/Game/Character/Animations/Armed_Attack_Montage.Armed_Attack_Montage'";
	ConstructorHelpers::FObjectFinder<UAnimMontage> attack(*path);
	if (attack.Succeeded())
		AttackMontage = attack.Object;
}

void ACPlayer::BeginPlay()
{
	Super::BeginPlay();

	UAIPerceptionSystem::RegisterPerceptionStimuliSource(this, UAISense_Sight::StaticClass(), this);

	SpringArm = Cast<USpringArmComponent>(GetComponentByClass(USpringArmComponent::StaticClass()));
	checkf(SpringArm, L"SpringArm != NULL");


	FTransform transform = FTransform::Identity;
	FActorSpawnParameters params;
	params.Owner = this;

	Sword = GetWorld()->SpawnActor<ACSword>(SwordClass, transform, params);
	Sword->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), "WeaponHolsterSocket");

	//OnEquip();
}

void ACPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ACPlayer::OnMoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACPlayer::OnMoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &ACPlayer::OnTurn);
	PlayerInputComponent->BindAxis("LookUp", this, &ACPlayer::OnLookUp);
	PlayerInputComponent->BindAxis("Zoom", this, &ACPlayer::OnZoom);

	PlayerInputComponent->BindAction("Running", EInputEvent::IE_Pressed, this, &ACPlayer::OnRunning);
	PlayerInputComponent->BindAction("Running", EInputEvent::IE_Released, this, &ACPlayer::OffRunning);

	PlayerInputComponent->BindAction("Jumping", EInputEvent::IE_Pressed, this, &ACPlayer::OnJumping);
	PlayerInputComponent->BindAction("Jumping", EInputEvent::IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction("Sword", EInputEvent::IE_Pressed, this, &ACPlayer::OnEquip);
	PlayerInputComponent->BindAction("Attacking", EInputEvent::IE_Pressed, this, &ACPlayer::OnAttacking);
}

void ACPlayer::OnMoveForward(float Value)
{
	bFoward = Value > 0.1f;
	if (bCanMove == false) return;

	FRotator rotation = GetControlRotation();
	FRotator temp = FRotator(0, rotation.Yaw, 0);
	FVector forward = FQuat(temp).GetForwardVector();

	AddMovementInput(forward, Value);
}

void ACPlayer::OnMoveRight(float Value)
{
	if (bCanMove == false) return;

	FRotator rotation = GetControlRotation();
	FRotator temp = FRotator(0, rotation.Yaw, 0);
	FVector right = FQuat(temp).GetRightVector();

	AddMovementInput(right, Value);
}

void ACPlayer::OnTurn(float Value)
{
	AddControllerYawInput(Value);
}

void ACPlayer::OnLookUp(float Value)
{
	AddControllerPitchInput(Value);
}

void ACPlayer::OnZoom(float Value)
{
	SpringArm->TargetArmLength += (ZoomSpeed * Value);
}

void ACPlayer::OnRunning()
{
	GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
}

void ACPlayer::OffRunning()
{
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

void ACPlayer::OnJumping()
{
	if (bCanMove == false) return;

	Jump();
}

void ACPlayer::OnEquip()
{
	if (bDrawing == true) return;
	
	if (bDrawn == false)
	{
		Equip();

		return;
	}

	if (GetCharacterMovement()->IsFalling() == false)
		Sheath();
}

void ACPlayer::OnAttacking()
{
	if (bDrawn == false) return;
	if (bAttacking == true) return;

	bAttacking = true;

	RetNull(AttackMontage);
	PlayAnimMontage(AttackMontage, 1.5f);
}

void ACPlayer::Equip()
{
	bDrawing = true;
	bCanMove = false;
}

void ACPlayer::Sheath()
{
	bSheathing = true;
	bCanMove = false;
}

void ACPlayer::Equipped()
{
	bDrawing = false;
	bDrawn = true;
	bCanMove = true;

	bUseControllerRotationYaw = true;
	GetCharacterMovement()->bOrientRotationToMovement = false;
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

void ACPlayer::Sheathed()
{
	bSheathing = false;
	bDrawn = false;
	bCanMove = true;
	
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

void ACPlayer::BeginAttack()
{
	bAttacking = true;
}

void ACPlayer::EndAttack()
{
	bAttacking = false;
}
