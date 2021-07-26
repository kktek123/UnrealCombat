// Fill out your copyright notice in the Description page of Project Settings.


#include "CGhostTrail.h"
#include "Global.h"
#include "MyGameProject/CParty.h"
#include "CCombatCharacter.h"
#include "Components/PoseableMeshComponent.h"
#include "Kismet/KismetMaterialLibrary.h"
#include "Materials/MaterialInstanceDynamic.h"

// Sets default values
ACGhostTrail::ACGhostTrail()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PoseableMesh = CreateDefaultSubobject<UPoseableMeshComponent>(TEXT("PoseableMesh"));
	SetRootComponent(PoseableMesh);

	FString path = L"CurveFloat'/Game/MyGameProjection/Alpha/Opacity.Opacity'";
	ConstructorHelpers::FObjectFinder<UCurveFloat> curve(*path);
	if (curve.Succeeded())
		CurveFloat = curve.Object;

}

// Called when the game starts or when spawned
void ACGhostTrail::BeginPlay()
{
	Super::BeginPlay();
	
	FOnTimelineEvent UpdatetimelineEvent;
	UpdatetimelineEvent.BindUFunction(this, "UpdateProgress");
	Opacity.SetTimelinePostUpdateFunc(UpdatetimelineEvent);

	FOnTimelineFloat progress;
	progress.BindUFunction(this, "Progress");

	Opacity.AddInterpFloat(CurveFloat, progress);
	Opacity.SetLooping(false);
	Opacity.SetTimelineLengthMode(TL_LastKeyFrame);

	FOnTimelineEvent timelineEvent;//
	timelineEvent.BindUFunction(this, "ResetProgress");//리셋
	Opacity.SetTimelineFinishedFunc(timelineEvent);//상황에따라 이벤트 콜



	PCR = Cast<ACCombatCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));
	GhostTrial();
}

void ACGhostTrail::GhostTrial()
{
	for (UMaterialInterface* i : PoseableMesh->GetMaterials())
	{
		
		//FString path = L"Material'/Game/M_GhostTrail.M_GhostTrail'";
		//ConstructorHelpers::FObjectFinder<UMaterialInterface> mat(*path);
		//if (mat.Succeeded())
		//	M_GhostTrail = mat.Object;

		UMaterialInstanceDynamic* result = UKismetMaterialLibrary::CreateDynamicMaterialInstance(this, M_GhostTrail);

		PoseableMesh->SetMaterial(Dynamicmats.Add(result)
			, (UMaterialInterface*)result);

		PoseableMesh->CopyPoseFromSkeletalComponent(PCR->GetMesh());
		Opacity.PlayFromStart();

	}
}

// Called every frame
void ACGhostTrail::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (Opacity.IsPlaying())
		Opacity.TickTimeline(DeltaTime);
}

void ACGhostTrail::Progress(float Value)
{
	newOpacity = Value;
	
}

void ACGhostTrail::ResetProgress()
{
	Destroy();
}

void ACGhostTrail::UpdateProgress()
{
	for (UMaterialInstanceDynamic* i : Dynamicmats)
	{
		i->SetScalarParameterValue("Opacity", newOpacity);
	}
}

