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
		float Location_Left;//�޹� ��ġ

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float Location_Right;//������ ��ġ

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float HipOffset;//������(����) ��ġ

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		FRotator Rotation_Left;//�޹� ȸ����

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		FRotator Rotation_Right;//������ ȸ����
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class U1908_04_COMBAT_API UCInverseKinemetics : public UActorComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Inverse Kinemetics")
		FName LeftFootSocket = "Foot_L";//�޹� �� �̸�

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Inverse Kinemetics")
		FName RightFootSocket = "Foot_R";//������ �� �̸�

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Inverse Kinemetics")
		float TraceDistance = 55.0f;//���� Ʈ���̽� ��ġ

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Inverse Kinemetics")
		float AdjustOffset = 5.0f; //�߰� �� ������ ����

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Inverse Kinemetics")
		float HipsInterpSpeed = 17.0f; //������ ���� �ӵ�

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Inverse Kinemetics")
		float FeetInterpSpeed = 22.0f;//�� ���� �ӵ�

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Inverse Kinemetics")
		bool bDebugDraw = false;//���� Ʈ���̽� ��ο�

public:	
	UCInverseKinemetics();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, 
		FActorComponentTickFunction* ThisTickFunction) override;

private:
	float Trace(FName Socket, FVector& OutImpactNormal);//���� Ʈ���̽� �浹 ��ġ ����ϰ� ���� ����
	FRotator NormalToRotator(FVector Normal);//���� ȸ���� ���

private:
	class ACharacter* Character;//����Ǵ� ĳ������

	float CapsuleHalfHeight;//���� Ʈ���̽� ������ ���
	FInverseKinemetics Ik;

public:
	FInverseKinemetics& GetEffector() { return Ik; }//������Ʈ�ѷ��� ������ ����
};
