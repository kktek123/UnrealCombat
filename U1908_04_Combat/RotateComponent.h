
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Enums/CEnum0.h"
#include "UIRotate.h"
#include "RotateComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class U1908_04_COMBAT_API URotateComponent : public UActorComponent , public IUIRotate
{
	GENERATED_BODY()

public:
	URotateComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void StartRotatingWithLimit(float MaxPossibleRotation, float MaxDegreesPerSecond);
	void StopRotating();
	void Debug();
	void StartRotatingWithTime(float Time, float MaxDegreesPerSecond);

	void SetRotationMode(E_RotationMode RotationMode);
	bool IsRotating();
	//virtual FRotator GetDesireRotation() const;
private:
	float TimeElapsed;
	float RotateTime;
	float MaxDegreesPerSecond;
	bool ShouldRotate;
	float MaxAllowedDegrees;

};