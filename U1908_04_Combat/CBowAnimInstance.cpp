// Fill out your copyright notice in the Description page of Project Settings.


#include "CBowAnimInstance.h"
#include "Global.h"
#include "MyGameProject/Item/CDI_Bow.h"
#include "CEnemy.h"
#include "CCStateManager.h"

UCBowAnimInstance::UCBowAnimInstance()
{

}

void UCBowAnimInstance::NativeBeginPlay()
{
	Item = Cast<ACDI_Bow>(GetOwningActor());
}

void UCBowAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	RetNull(Item);

	AimAlpha = Item->GetAimAlpha();
}

