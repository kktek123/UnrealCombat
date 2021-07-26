// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CAudioActor.generated.h"

UENUM(BlueprintType)
enum class E_Musiclist : uint8
{
	Normal UMETA(DisplayName = "Normal"),
	Fight UMETA(DisplayName = "Fight"),
	Final UMETA(DisplayName = "Final"),
};

UCLASS()
class U1908_04_COMBAT_API ACAudioActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACAudioActor();

	UPROPERTY(EditAnywhere)
		class UAudioComponent* AudioComp;

	UPROPERTY(EditAnywhere)
		class UAudioComponent* AudioComp1;

	UPROPERTY(EditAnywhere)
		class UAudioComponent* AudioComp2;

	UFUNCTION()
		void PlayMusic(uint32 musiclist);

	UFUNCTION()
		void FadeOut();

	UPROPERTY(EditAnywhere)
		TArray<USoundBase*>Musiclist;
	UPROPERTY(EditAnywhere)
		bool bGetInBossRoom;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
