// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyGameProject/Item/CDisplayedItem.h"
#include "CDI_Spell.generated.h"

/**
 * 
 */
UCLASS()
class U1908_04_COMBAT_API ADI_Spell : public ACDisplayedItem
{
	GENERATED_BODY()
	
public:
	ADI_Spell(const class FObjectInitializer& Object);

private:
	FName HandAttachmentSocket;
	E_MagicType magicType;
	class ACCombatCharacter* player;
	

};
