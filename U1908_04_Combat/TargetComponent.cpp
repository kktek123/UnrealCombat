// Fill out your copyright notice in the Description page of Project Settings.


#include "TargetComponent.h"
#include "Global.h"
#include "Components/ArrowComponent.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "CEnemy.h"
#include "Blueprint/WidgetLayoutLibrary.h"

EDrawDebugTrace::Type DebugMode;

UTargetComponent::UTargetComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	
	FString path = L"Class'/Script/U1908_04_Combat.UITargetable'";
	ConstructorHelpers::FClassFinder<UUITargetable> widget(*path);
	if (widget.Succeeded())
		targetable = widget.Class;

}

void UTargetComponent::BeginPlay()
{
	Super::BeginPlay();
	SetDebugMode();
	CheckCollisionTypeArrays();
	CharacterReference = Cast<ACharacter>(GetOwner());
	
}

void UTargetComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UpdateCameraLock();
}

void UTargetComponent::Initialize(UArrowComponent * UArrowComponent)
{
	RetNull(UArrowComponent);
	ArrowComponent = UArrowComponent;
	ArrowComponent->bAbsoluteRotation = true;
}

void UTargetComponent::DisableCameraLock()
{
	if (bIsTargetingEnabled)
	{
		bIsTargetingEnabled = false;
		Cast<ACEnemy>(SelectedActor)->OnDeselected();
		UKismetSystemLibrary::K2_ClearAndInvalidateTimerHandle(GetWorld(), CheckTargetHandle);
		UpdateIgnoreLookInput();
	}
}

void UTargetComponent::FindTargetWithAxisInput(float Axisvalue)
{
	float StartRotatingThreadhold = 1.5f;
	if (IsValid(ArrowComponent) && IsValid(SelectedActor)
		&& UKismetMathLibrary::Abs(Axisvalue) > StartRotatingThreadhold
		&& !bIsFreeCamera)
	{
		if (UKismetMathLibrary::Abs(
				UKismetMathLibrary::NormalizedDeltaRotator(
					GetOwner()->Instigator->GetControlRotation(),
					ArrowComponent->GetComponentRotation()).Yaw)
			<= 165)
		{
			
			float fclampvalue = Axisvalue * AxisInputSensitivity;
			float fclampmax = UKismetSystemLibrary::MakeLiteralFloat(625)*UGameplayStatics::GetWorldDeltaSeconds(this);
			float fclampmin = fclampmax * -1;
			float fclamp = UKismetMathLibrary::FClamp(fclampvalue, fclampmin, fclampmax);
			ArrowComponent->AddLocalRotation(FRotator(0, 0, fclamp));

		}
		FVector Start = ArrowComponent->GetComponentLocation();
		FVector End = ArrowComponent->GetComponentLocation() + 
			ArrowComponent->GetForwardVector() * TargetingMaxDistance;
		TArray<AActor*> actorempty;
		TArray<FHitResult> OutHit;
		UKismetSystemLibrary::CapsuleTraceMultiForObjects(GetWorld(), Start,End
		,32,TargetingMaxHeight,AllowedCollisionTypes,false, actorempty, DebugMode, OutHit,true);
		for (FHitResult Hit : OutHit)
		{
			bool Blockinghit;
			bool IO;
			float t;
			float d;
			FVector L;
			FVector ip;
			FVector N;
			FVector ImpactN;
			UPhysicalMaterial* PM;
			AActor* HitActor;
			UPrimitiveComponent* HC;
			FName HB;
			int HI;
			int FI;
			FVector TS;
			FVector TE;
			UGameplayStatics::BreakHitResult(Hit, Blockinghit, IO,t,d,L,ip,N, ImpactN, PM,HitActor,HC,HB,HI,FI,TS,TE);
			if(Blockinghit)
				if (SelectedActor != HitActor)
				{
					TArray<AActor*> AtI;
					if(!IsAnythingBlockingTrace(HitActor, AtI))
					{
						if(Cast<ACEnemy>(HitActor)->IsTargetable())
						{
							Cast<ACEnemy>(SelectedActor)->OnDeselected();
							SelectedActor = HitActor;
							Cast<ACEnemy>(SelectedActor)->OnSelected();
						}
					}
				}
				
		}

		//if()
	}


}

void UTargetComponent::ToggleCameraLock()
{
	
	if (IsTargetingEnabled())
		DisableCameraLock();
	else
		FindTarget();

}

bool UTargetComponent::IsTargetingEnabled()
{
	return bIsTargetingEnabled;
}

void UTargetComponent::FindTargetOnLeft()
{
	FindDirectionalTarget(true);
}

void UTargetComponent::FindTargetOnRight()
{
	FindDirectionalTarget(false);
}

void UTargetComponent::SetFreeCamera(bool FreeCamera)
{
	bIsFreeCamera = FreeCamera;
	UpdateIgnoreLookInput();
}

void UTargetComponent::FindTarget()
{
	TArray<AActor*> OutActors;
	TArray<AActor*> PotentialTargets;
	AActor *LocalPotentialTarget;
	float DistanceFromCenterOfViewport = 0;
	UGameplayStatics::GetAllActorsWithInterface(GetWorld(), targetable, OutActors);
	for (AActor* a : OutActors)//화면안의 객체들을 PotentialTargets에 넣는다.
	{
		LocalPotentialTarget = a;
		if (Cast<ACEnemy>(LocalPotentialTarget)->IsTargetable()
			&& UKismetSystemLibrary::DoesImplementInterface(LocalPotentialTarget, targetable)
			&& GetOwner() != SelectedActor)
		{
			if (IsInViewport(GetActorScreenPosition(LocalPotentialTarget).Key)
				&& GetActorScreenPosition(LocalPotentialTarget).Value
				&&GetDistanceToOwner(LocalPotentialTarget) <= TargetingMaxDistance)
			{
				if (!IsAnythingBlockingTrace(LocalPotentialTarget, PotentialTargets))
					PotentialTargets.Add(LocalPotentialTarget);
			}
		}
	}
	for (AActor* a : PotentialTargets)//가까운 액터를 우선적으로 SelectedActor한다.
	{
		LocalPotentialTarget = a;
		float abs = UKismetMathLibrary::Abs(GetActorScreenPosition(LocalPotentialTarget).Key.X - (UWidgetLayoutLibrary::GetViewportSize(GetWorld()).X / 2));
		if (a == PotentialTargets[0])
		{
			DistanceFromCenterOfViewport = abs;
			SelectedActor = LocalPotentialTarget;
		}
		else if(abs < DistanceFromCenterOfViewport)
		{
			DistanceFromCenterOfViewport = abs;
			SelectedActor = LocalPotentialTarget;
		}
	}
	RetNull(SelectedActor);
	EnableCameraLock();

}

bool UTargetComponent::IsInViewport(FVector2D screenpos)
{
	float SX, SY;
	float GX, GY;
	UKismetMathLibrary::BreakVector2D(screenpos, SX, SY);
	UKismetMathLibrary::BreakVector2D(UWidgetLayoutLibrary::GetViewportSize(GetWorld()), GX, GY);
	if (SX > 0 && SY > 0 && SX <= GX && SY <= GY)
		return true;
	else
		return false;
}

FVector UTargetComponent::GetLineTraceStartLocation()
{
	FVector startlocation = GetOwner()->GetActorLocation() +
		GetOwner()->GetActorForwardVector()*TraceDepthOffset +
		GetOwner()->GetActorUpVector()*TraceHeightOffset;
	return startlocation;
}

void UTargetComponent::EnableCameraLock()
{
	if (!Cast<ACEnemy>(SelectedActor)->IsTargetable())return;
	bIsTargetingEnabled = true;
	UKismetSystemLibrary::K2_ClearAndInvalidateTimerHandle(GetWorld(),DisableCameraLockHandle);
	SetDebugMode();
	Cast<ACEnemy>(SelectedActor)->OnSelected();
	//SelectedActor->GetWorldTimerManager().SetTimer(CheckTargetHandle, this, &UTargetComponent::CheckTarget, 0.15f, true);
	UpdateIgnoreLookInput();
	//OnTargetingToggled
}

void UTargetComponent::UpdateCameraLock()
{
	if (IsTargetingEnabled())
	{
		float GetDistance = GetOwner()->GetDistanceTo(SelectedActor);
		Cast<ACEnemy>(SelectedActor)->OnDead.AddLambda([&]()
		{
			DisableCameraLock();
		});
		if (GetDistance < 50 && GetDistance >= TargetingMaxDistance)
			DisableCameraLock();
		else
		{
			if (IsValid(ArrowComponent))
			{
				ArrowComponent->SetWorldRotation(FRotator(0, 0, 
					UKismetMathLibrary::RInterpTo_Constant(ArrowComponent->GetComponentRotation(),
						GetOwner()->Instigator->GetControlRotation(), 
						UGameplayStatics::GetWorldDeltaSeconds(this), 250).Yaw));
			}
			if (!bIsFreeCamera)
			{
				FRotator Target = UKismetMathLibrary::FindLookAtRotation(GetOwner()->GetActorLocation(), SelectedActor->GetActorLocation());

				GetOwner()->Instigator->GetController()->SetControlRotation(
					UKismetMathLibrary::RInterpTo_Constant(
						GetOwner()->Instigator->GetControlRotation(), Target,
					UGameplayStatics::GetWorldDeltaSeconds(this), 300));
			}
		}
	}
		

}

void UTargetComponent::SetDebugMode()
{
	//Debug = 
	if (Debug)
		DebugMode = EDrawDebugTrace::ForDuration;
	else
		DebugMode = EDrawDebugTrace::None;
}

void UTargetComponent::CheckTarget()
{
	TArray<AActor*> AtI;
	if (IsAnythingBlockingTrace(SelectedActor, AtI))
	{
		if (!UKismetSystemLibrary::K2_IsTimerActiveHandle(this, DisableCameraLockHandle))
			if (DisableOnBlockDelay == 0)
				DisableCameraLock();
			else
				GetOwner()->GetWorldTimerManager().SetTimer(DisableCameraLockHandle, this, &UTargetComponent::DisableCameraLock, DisableOnBlockDelay, false);

	}
	else
	{
		UKismetSystemLibrary::K2_ClearAndInvalidateTimerHandle(GetWorld(), DisableCameraLockHandle);
		if (!Cast<ACEnemy>(SelectedActor)->IsTargetable())
		{
			DisableCameraLock();
			FindTarget();
		}
	}
}

void UTargetComponent::FindDirectionalTarget(bool OnLeft)
{
	TArray<AActor*> OutActors;
	TArray<AActor*> PotentialTargets;
	TArray<AActor*> PotentialTargetsRight;
	TArray<AActor*> PotentialTargetsLeft;
	AActor *LocalPotentialTarget = NULL;
	bool LocalOnLeft;
	LocalOnLeft = OnLeft;
	if (IsTargetingEnabled())
	{
		UGameplayStatics::GetAllActorsWithInterface(GetWorld(), targetable, OutActors);
		for (AActor* a : OutActors)
		{
			LocalPotentialTarget = a;
			if (Cast<ACEnemy>(LocalPotentialTarget)->IsTargetable()
				&& UKismetSystemLibrary::DoesImplementInterface(GetWorld(), targetable)
				&& LocalPotentialTarget != SelectedActor
				&& GetOwner() != SelectedActor)
			{
				if (GetDistanceToOwner(LocalPotentialTarget) <= TargetingMaxDistance)
				{
					if (!IsAnythingBlockingTrace(LocalPotentialTarget, PotentialTargetsRight))
					{
						if (!IsAnythingBlockingTrace(LocalPotentialTarget, PotentialTargetsLeft))
						{
							if (TargetSide(LocalPotentialTarget))
								PotentialTargetsRight.Add(LocalPotentialTarget);
							else
								PotentialTargetsLeft.Add(LocalPotentialTarget);

						}
					}
				}
			}
		}
		if (LocalOnLeft)
		{
			if (HasArrayAnyElem(PotentialTargetsLeft))
				LocalPotentialTarget = GetTargetByDotProduct(PotentialTargetsLeft, true);
			else
				LocalPotentialTarget = GetTargetByDotProduct(PotentialTargetsRight, false);
		}
		else
		{
			if (HasArrayAnyElem(PotentialTargetsRight))
				LocalPotentialTarget = GetTargetByDotProduct(PotentialTargetsRight, true);
			else
				LocalPotentialTarget = GetTargetByDotProduct(PotentialTargetsLeft, false);
		}
		RetNull(LocalPotentialTarget);
		Cast<ACEnemy>(SelectedActor)->OnDeselected();
		SelectedActor = LocalPotentialTarget;
		Cast<ACEnemy>(SelectedActor)->OnSelected();

	}
}

AActor * UTargetComponent::GetTargetByDotProduct(TArray<AActor*> Array, bool Best)
{
	float LocalDotProduct = 0;
	AActor* LocalPotentialTarget = NULL;
	bool LocalBest = false;
	LocalBest = Best;
	for (AActor* a : Array)
	{
		float CDPT = CalculateDotProductToTarget(a);
		if (CDPT < LocalDotProduct)
			LocalBest = false;
		else if (CDPT > LocalDotProduct)
			LocalBest = true;

		if (a == Array[0])
		{
			LocalDotProduct = CDPT;
			LocalPotentialTarget = a;
		}
		else if (LocalBest)
		{
			LocalDotProduct = CDPT;
			LocalPotentialTarget = a;
		}
	}
	return LocalPotentialTarget;
}



void UTargetComponent::UpdateIgnoreLookInput()
{
	RetNull(GetOwner()->Instigator->GetController());
	if (IsTargetingEnabled() && !bIsFreeCamera)
		GetOwner()->Instigator->GetController()->SetIgnoreLookInput(true);
	else
		GetOwner()->Instigator->GetController()->ResetIgnoreLookInput();
}

bool UTargetComponent::IsAnythingBlockingTrace(AActor* target, TArray<AActor*> ActorsToIgnore)
{
	FHitResult OutHit;

	if (BlockingCollisionTypes.Num() > 0)
	{
		if (UKismetSystemLibrary::LineTraceSingleForObjects(
			GetWorld(), GetLineTraceStartLocation(), target->GetActorLocation(),
			BlockingCollisionTypes, false, ActorsToIgnore, DebugMode, OutHit, true))
		{
			return true;
		}
		else
			return false;
	}
		return false;
}

void UTargetComponent::CheckCollisionTypeArrays()
{
	for (TEnumAsByte<EObjectTypeQuery> a : AllowedCollisionTypes)
	{
		BlockingCollisionTypes.Remove(a);
	}
}

TPair<FVector2D, bool> UTargetComponent::GetActorScreenPosition(AActor * actor)
{
	FVector2D SP;
	bool RV;
	RV = UGameplayStatics::ProjectWorldToScreen(
		UGameplayStatics::GetPlayerController(GetWorld(), 0), 
		actor->GetActorLocation(), SP, false);
	
	return TPair<FVector2D, bool>(SP, RV);
}


float UTargetComponent::GetDistanceToOwner(AActor* OtherActor)
{
	return 	GetOwner()->GetDistanceTo(OtherActor);
}

bool UTargetComponent::TargetSide(AActor* PotentialTarget)
{
	FVector a = UKismetMathLibrary::GetDirectionUnitVector(GetOwner()->GetActorLocation(), SelectedActor->GetActorLocation());
	FVector b = UKismetMathLibrary::GetDirectionUnitVector(GetOwner()->GetActorLocation(), PotentialTarget->GetActorLocation());
	float result = UKismetMathLibrary::Dot_VectorVector(UKismetMathLibrary::Cross_VectorVector(a, b),GetOwner()->GetActorUpVector());
	if (result >= 0)
		return true;
	else
		return false;
}

float UTargetComponent::CalculateDotProductToTarget(AActor* Target)
{
	float result;
	FVector a, b;
	a = UKismetMathLibrary::GetDirectionUnitVector(GetOwner()->GetActorLocation(), SelectedActor->GetActorLocation());
	b = UKismetMathLibrary::GetDirectionUnitVector(GetOwner()->GetActorLocation(), Target->GetActorLocation());
	result = UKismetMathLibrary::Dot_VectorVector(a, b);
	
	return result;
}

bool UTargetComponent::HasArrayAnyElem(TArray<AActor*> ActorsToIgnore)
{
	if (ActorsToIgnore.Num() > 0)
		return true;
	return false;
}
