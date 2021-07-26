// Fill out your copyright notice in the Description page of Project Settings.


#include "CRotateOwner.h"
#include "Global.h"
#include "CCombatCharacter.h"
#include "CEnemy.h"
#include "RotateComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

UCRotateOwner::UCRotateOwner()
{
	FString path = L"Class'/Script/U1908_04_Combat.RotateComponent'";
	ConstructorHelpers::FClassFinder<URotateComponent> shield(*path);
	if (shield.Succeeded())
		ComponentClass = shield.Class;

}

void UCRotateOwner::NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);
	RetNull(MeshComp->GetOwner());
	if (MeshComp->GetOwner()->IsA(ACEnemy::StaticClass()))
	{
		ACEnemy* enemy = Cast<ACEnemy>(MeshComp->GetOwner());
		enemy->GetRotateComponent()->StartRotatingWithTime(10, MaxDegreesPerSecond);
		//enemy->GetRotateComponent()->SetRotationMode(E_RotationMode::OrientToMovement);
		//enemy->GetCharacterMovement()->bUseControllerDesiredRotation = true;
		//enemy->GetCharacterMovement()->bOrientRotationToMovement = false;

		//RetNull(MeshComp->GetOwner()->GetComponentByClass(ComponentClass));
		//CLog::Print(TEXT("NotifyBegin"));

	}

}

void UCRotateOwner::NotifyTick(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float FrameDeltaTime)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime);
}

void UCRotateOwner::NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	Super::NotifyEnd(MeshComp, Animation);
	RetNull(MeshComp->GetOwner());
	//RetNull(MeshComp->GetOwner()->GetComponentByClass(ComponentClass));
	//RotateComponent->StopRotating();
	if (MeshComp->GetOwner()->IsA(ACEnemy::StaticClass()))
	{
		ACEnemy* enemy = Cast<ACEnemy>(MeshComp->GetOwner());
		enemy->GetRotateComponent()->StopRotating();
		//enemy->GetRotateComponent()->SetRotationMode(E_RotationMode::FaceCamera);
		//enemy->GetCharacterMovement()->bUseControllerDesiredRotation = false;
		//enemy->GetCharacterMovement()->bOrientRotationToMovement = true;
		
	}

}
