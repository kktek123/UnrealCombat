// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UITargetable.h"
#include "Components/ActorComponent.h"
#include "TargetComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class U1908_04_COMBAT_API UTargetComponent : public UActorComponent ,public IUITargetable
{
	GENERATED_BODY()

public:	
	UTargetComponent();

protected:
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
		FActorComponentTickFunction* ThisTickFunction) override;

	void Initialize(class UArrowComponent* UArrowComponent);//타겟 초기화
	void DisableCameraLock();//타겟팅을 하지 않습니다.
	
	void ToggleCameraLock();//타겟팅을 시도합니다.
	bool IsTargetingEnabled();//타겟을 찾았습니다.
	void FindTargetOnLeft();//왼편의 타겟으로 전환합니다.
	void FindTargetOnRight();//오른편의 타겟으로 전환합니다.
	void SetFreeCamera(bool FreeCamera);//카메라를 고정을 풉니다.


private:
	void FindTarget();//타겟팅할 엑터들의 집합을 만듭니다.
	bool IsInViewport(FVector2D screenpos);//화면안에 엑터가 있는지 여부
	FVector GetLineTraceStartLocation();//타겟을 탐지하는 라인트레이스 시작점
	void EnableCameraLock();//카메라를 고정합니다.
	void UpdateCameraLock();//상황에 따라 카메라 고정여부를 정합니다.
	void SetDebugMode();//타겟위젯을 표시합니다.
	void FindDirectionalTarget(bool OnLeft);//왼쪽이나 오른쪽에 타겟을 탐색합니다.
	AActor* GetTargetByDotProduct(TArray<AActor*> Array, bool Best);
	//우선적으로 타겟팅될 엑터를 선택합니다.
	void UpdateIgnoreLookInput();//카메라 회전여부
public:
	UPROPERTY(EditAnywhere)
		float AxisInputSensitivity = 1.5;
	float TargetingMaxDistance = 2500;//타겟 가능 범위
	float TargetingMaxHeight = 640;//타겟 가능 높이
	float TraceDepthOffset;//라인 트레이스 시작
	float TraceHeightOffset = 100;//라인 트레이스 시작
	AActor* SelectedActor;//타겟된 엑터
	UPROPERTY(VisibleAnywhere)
	TSubclassOf<UInterface> targetable;//타겟가능 인터페이스
	UPROPERTY(EditDefaultsOnly)
	TArray<TEnumAsByte<EObjectTypeQuery>> AllowedCollisionTypes;//라인트레이스가 반응히는 타입
	// = EObjectTypeQuery::ObjectTypeQuery3;
	UPROPERTY(EditDefaultsOnly)
	TArray<TEnumAsByte<EObjectTypeQuery>> BlockingCollisionTypes;//라인트레이스가 막히는 타입
	float DisableOnBlockDelay = 2;//타겟팅이 풀리는 시간

private:
	bool IsAnythingBlockingTrace(AActor* target, TArray<AActor*> ActorsToIgnore);//타겟이 소실되었을때 락을 풉니다.
	void CheckCollisionTypeArrays();//타겟집합을 초기화합니다.
	TPair<FVector2D, bool> GetActorScreenPosition(AActor* actor);//타겟의 화면에서의 위치
	float GetDistanceToOwner(AActor* OtherActor);//타겟과 자신의 거리
	float CalculateDotProductToTarget(AActor* Target);//자신부터 타겟사이의 회전값

	//
private:
	bool bIsTargetingEnabled;
	UPROPERTY(EditDefaultsOnly)
	bool Debug;
	ACharacter* CharacterReference;
	FTimerHandle CheckTargetHandle;
	bool bIsFreeCamera;
	FTimerHandle DisableCameraLockHandle;
	class UArrowComponent* ArrowComponent;

public:
	void FindTargetWithAxisInput(float Axisvalue);//이동에 따라 타겟을 찾습니다.
private:
	void CheckTarget();
	bool TargetSide(AActor* PotentialTarget);
	bool HasArrayAnyElem(TArray<AActor*> ActorsToIgnore);

};
