#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CSword.generated.h"

UCLASS()
class U1908_04_COMBAT_API ACSword : public AActor
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditDefaultsOnly)
		float Power = 20.0f;

	UPROPERTY(VisibleAnywhere)
		class USkeletalMeshComponent* Mesh;
	
	UPROPERTY(VisibleAnywhere)
		class UCapsuleComponent* Capsule;

public:
	UFUNCTION(BlueprintPure)
		class UCapsuleComponent* GetCapsule() { return Capsule; }

private:
	UFUNCTION()
		void OnBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
		void OnEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:	
	ACSword();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
};
