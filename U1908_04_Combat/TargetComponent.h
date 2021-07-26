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

	void Initialize(class UArrowComponent* UArrowComponent);//Ÿ�� �ʱ�ȭ
	void DisableCameraLock();//Ÿ������ ���� �ʽ��ϴ�.
	
	void ToggleCameraLock();//Ÿ������ �õ��մϴ�.
	bool IsTargetingEnabled();//Ÿ���� ã�ҽ��ϴ�.
	void FindTargetOnLeft();//������ Ÿ������ ��ȯ�մϴ�.
	void FindTargetOnRight();//�������� Ÿ������ ��ȯ�մϴ�.
	void SetFreeCamera(bool FreeCamera);//ī�޶� ������ Ǳ�ϴ�.


private:
	void FindTarget();//Ÿ������ ���͵��� ������ ����ϴ�.
	bool IsInViewport(FVector2D screenpos);//ȭ��ȿ� ���Ͱ� �ִ��� ����
	FVector GetLineTraceStartLocation();//Ÿ���� Ž���ϴ� ����Ʈ���̽� ������
	void EnableCameraLock();//ī�޶� �����մϴ�.
	void UpdateCameraLock();//��Ȳ�� ���� ī�޶� �������θ� ���մϴ�.
	void SetDebugMode();//Ÿ�������� ǥ���մϴ�.
	void FindDirectionalTarget(bool OnLeft);//�����̳� �����ʿ� Ÿ���� Ž���մϴ�.
	AActor* GetTargetByDotProduct(TArray<AActor*> Array, bool Best);
	//�켱������ Ÿ���õ� ���͸� �����մϴ�.
	void UpdateIgnoreLookInput();//ī�޶� ȸ������
public:
	UPROPERTY(EditAnywhere)
		float AxisInputSensitivity = 1.5;
	float TargetingMaxDistance = 2500;//Ÿ�� ���� ����
	float TargetingMaxHeight = 640;//Ÿ�� ���� ����
	float TraceDepthOffset;//���� Ʈ���̽� ����
	float TraceHeightOffset = 100;//���� Ʈ���̽� ����
	AActor* SelectedActor;//Ÿ�ٵ� ����
	UPROPERTY(VisibleAnywhere)
	TSubclassOf<UInterface> targetable;//Ÿ�ٰ��� �������̽�
	UPROPERTY(EditDefaultsOnly)
	TArray<TEnumAsByte<EObjectTypeQuery>> AllowedCollisionTypes;//����Ʈ���̽��� �������� Ÿ��
	// = EObjectTypeQuery::ObjectTypeQuery3;
	UPROPERTY(EditDefaultsOnly)
	TArray<TEnumAsByte<EObjectTypeQuery>> BlockingCollisionTypes;//����Ʈ���̽��� ������ Ÿ��
	float DisableOnBlockDelay = 2;//Ÿ������ Ǯ���� �ð�

private:
	bool IsAnythingBlockingTrace(AActor* target, TArray<AActor*> ActorsToIgnore);//Ÿ���� �ҽǵǾ����� ���� Ǳ�ϴ�.
	void CheckCollisionTypeArrays();//Ÿ�������� �ʱ�ȭ�մϴ�.
	TPair<FVector2D, bool> GetActorScreenPosition(AActor* actor);//Ÿ���� ȭ�鿡���� ��ġ
	float GetDistanceToOwner(AActor* OtherActor);//Ÿ�ٰ� �ڽ��� �Ÿ�
	float CalculateDotProductToTarget(AActor* Target);//�ڽź��� Ÿ�ٻ����� ȸ����

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
	void FindTargetWithAxisInput(float Axisvalue);//�̵��� ���� Ÿ���� ã���ϴ�.
private:
	void CheckTarget();
	bool TargetSide(AActor* PotentialTarget);
	bool HasArrayAnyElem(TArray<AActor*> ActorsToIgnore);

};
