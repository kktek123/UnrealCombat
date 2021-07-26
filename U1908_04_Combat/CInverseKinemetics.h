#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CInverseKinemetics.generated.h"

USTRUCT(BlueprintType)
struct FInverseKinemetics
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float Location_Left;//왼발 위치

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float Location_Right;//오른발 위치

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float HipOffset;//엉덩이(엑터) 위치

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		FRotator Rotation_Left;//왼발 회전값

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		FRotator Rotation_Right;//오른발 회전값
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class U1908_04_COMBAT_API UCInverseKinemetics : public UActorComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Inverse Kinemetics")
		FName LeftFootSocket = "Foot_L";//왼발 본 이름

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Inverse Kinemetics")
		FName RightFootSocket = "Foot_R";//오른발 본 이름

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Inverse Kinemetics")
		float TraceDistance = 55.0f;//라인 트래이스 위치

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Inverse Kinemetics")
		float AdjustOffset = 5.0f; //발과 땅 사이의 간격

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Inverse Kinemetics")
		float HipsInterpSpeed = 17.0f; //엉덩이 보간 속도

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Inverse Kinemetics")
		float FeetInterpSpeed = 22.0f;//발 보간 속도

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Inverse Kinemetics")
		bool bDebugDraw = false;//라인 트래이스 드로우

public:	
	UCInverseKinemetics();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, 
		FActorComponentTickFunction* ThisTickFunction) override;

private:
	float Trace(FName Socket, FVector& OutImpactNormal);//라인 트레이스 충돌 위치 계산하고 값을 제공
	FRotator NormalToRotator(FVector Normal);//발의 회전값 계산

private:
	class ACharacter* Character;//적용되는 캐릭엑터

	float CapsuleHalfHeight;//라인 트레이스 시작점 계산
	FInverseKinemetics Ik;

public:
	FInverseKinemetics& GetEffector() { return Ik; }//에님컨트롤러에 정보값 전달
};
