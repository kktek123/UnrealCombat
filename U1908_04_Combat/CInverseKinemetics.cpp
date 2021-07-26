#include "CInverseKinemetics.h"
#include "Global.h"
#include "CCombatCharacter.h"
#include "GameFramework/Character.h"

UCInverseKinemetics::UCInverseKinemetics()
{
	PrimaryComponentTick.bCanEverTick = true;

	
}

void UCInverseKinemetics::BeginPlay()
{
	Super::BeginPlay();
	
	Character = Cast<ACharacter>(GetOwner());
	RetNull(Character);

	CapsuleHalfHeight = Character->GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight();
}


void UCInverseKinemetics::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector leftNormal, rightNormal;
	float leftTraceDistance = Trace(LeftFootSocket, leftNormal);
	float rightTraceDistance = Trace(RightFootSocket, rightNormal);
	

	float offset = UKismetMathLibrary::Min(leftTraceDistance, rightTraceDistance);
	offset = offset > 0.0f ? 0.0f : offset;

	
	float half = CapsuleHalfHeight - FMath::Abs(offset) * 0.5f;
	UCapsuleComponent* capsule = Character->GetCapsuleComponent();
	RetNull(capsule);

	float scaleHalf = capsule->GetScaledCapsuleHalfHeight();
	float interpValue = UKismetMathLibrary::FInterpTo(scaleHalf, half, DeltaTime, HipsInterpSpeed);

	capsule->SetCapsuleHalfHeight(interpValue);

	
	Ik.HipOffset = UKismetMathLibrary::FInterpTo(Ik.HipOffset, offset, DeltaTime, HipsInterpSpeed);//�ε��Ҽ�������

	Ik.Location_Left = UKismetMathLibrary::FInterpTo(Ik.Location_Left, leftTraceDistance - offset, DeltaTime, FeetInterpSpeed);//������Ʈ ����
	Ik.Location_Right = UKismetMathLibrary::FInterpTo(Ik.Location_Right, -(rightTraceDistance - offset), DeltaTime, FeetInterpSpeed);

	Ik.Rotation_Left = UKismetMathLibrary::RInterpTo(Ik.Rotation_Left, NormalToRotator(leftNormal), DeltaTime, FeetInterpSpeed);//������Ʈ ����
	Ik.Rotation_Right = UKismetMathLibrary::RInterpTo(Ik.Rotation_Right, NormalToRotator(rightNormal), DeltaTime, FeetInterpSpeed);
}

float UCInverseKinemetics::Trace(FName Socket, FVector & OutImpactNormal)
{
	FVector location = Character->GetMesh()->GetSocketLocation(Socket);
	FVector start = FVector(location.X, location.Y, Character->GetActorLocation().Z);//����ġ ��ȯ�ϴ� ������

	float z = start.Z - CapsuleHalfHeight - TraceDistance;
	FVector end = FVector(location.X, location.Y, z);//����ġ ��ȯ�ϴ� �ִ�Ÿ�


	TArray<AActor *> ignore;
	ignore.Add(GetOwner());

	FHitResult hit;
	EDrawDebugTrace::Type debug = bDebugDraw ? EDrawDebugTrace::ForOneFrame : EDrawDebugTrace::None;

	bool bHit = UKismetSystemLibrary::LineTraceSingle
	(
		GetWorld(), start, end, UEngineTypes::ConvertToTraceType(ECC_Visibility),
		true, ignore, debug, hit, true
	);

	OutImpactNormal = hit.ImpactNormal;//�浹�� ��ġ�� ���밪
	if (hit.IsValidBlockingHit())
	{
		float length = (hit.ImpactPoint - hit.TraceEnd).Size();

		return AdjustOffset + length - TraceDistance;
	}

	return 0.0f;
}

FRotator UCInverseKinemetics::NormalToRotator(FVector Normal)
{
	float t = UKismetMathLibrary::DegAtan2(Normal.Y, Normal.Z);
	float t2 = -UKismetMathLibrary::DegAtan2(Normal.X, Normal.Z);

	return FRotator(t2, 0.0f, t);
}

