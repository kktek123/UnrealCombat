// Fill out your copyright notice in the Description page of Project Settings.


#include "RotateComponent.h"
#include "Global.h"
#include "CEnemy.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

URotateComponent::URotateComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	MaxDegreesPerSecond = 720;
	MaxAllowedDegrees = 180;
	TimeElapsed = 0;
	RotateTime = 0;
	ShouldRotate = false;
}


void URotateComponent::BeginPlay()
{
	Super::BeginPlay();


}


void URotateComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (ShouldRotate)
	{
		TimeElapsed += UGameplayStatics::GetWorldDeltaSeconds(GetWorld());
		//CLog::Print(TimeElapsed);

		if (TimeElapsed <= RotateTime)
		{
			ACEnemy* enemy = Cast<ACEnemy>(GetOwner());
			FRotator NewRotation =
				UKismetMathLibrary::RInterpTo_Constant(GetOwner()->GetActorRotation(),
					enemy->GetDesireRotation(), UGameplayStatics::GetWorldDeltaSeconds(GetWorld()),
					MaxDegreesPerSecond);

			enemy->SetActorRotation(NewRotation);
		}
		else
			StopRotating();
	}
		
	
	
}

void URotateComponent::StartRotatingWithLimit(float mMaxPossibleRotation, float mMaxDegreesPerSecond)
{
	RotateTime = mMaxPossibleRotation / mMaxDegreesPerSecond;
	MaxDegreesPerSecond = mMaxDegreesPerSecond;
	TimeElapsed = 0;
	ShouldRotate = true;
}

void URotateComponent::StartRotatingWithTime(float Time, float mMaxDegreesPerSecond)
{
	RotateTime = Time;
	MaxDegreesPerSecond = mMaxDegreesPerSecond;
	TimeElapsed = 0;
	ShouldRotate = true;
}

void URotateComponent::StopRotating()
{
	ShouldRotate = false;
}

void URotateComponent::Debug()
{
}



void URotateComponent::SetRotationMode(E_RotationMode RotationMode)
{
	ACharacter* Character = Cast< ACharacter>(GetOwner());
	if (RotationMode == E_RotationMode::FaceCamera)
	{
		//Character->bUseControllerRotationYaw = false;
		Character->GetCharacterMovement()->bUseControllerDesiredRotation = true;
		Character->GetCharacterMovement()->bOrientRotationToMovement = false;

	}
	else if (RotationMode == E_RotationMode::OrientToMovement)
	{
		//Character->bUseControllerRotationYaw = false;
		Character->GetCharacterMovement()->bUseControllerDesiredRotation = false;
		Character->GetCharacterMovement()->bOrientRotationToMovement = true;

	}
}

bool URotateComponent::IsRotating()
{
	return ShouldRotate;
}

