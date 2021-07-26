// Fill out your copyright notice in the Description page of Project Settings.


#include "CBlockAlpha.h"
#include "Global.h"
#include "CCombatCharacter.h"
#include "Curves/CurveFloat.h"
#include "Components/SplineComponent.h"

ACBlockAlpha::ACBlockAlpha()
{
	PrimaryActorTick.bCanEverTick = true;

	//Spline = CreateDefaultSubobject<USplineComponent>("Spline");
	//RootComponent = Spline;

	FString path = L"CurveFloat'/Game/MyGameProjection/Alpha/BlockAlpha.BlockAlpha'";
	ConstructorHelpers::FObjectFinder<UCurveFloat> curve(*path);
	if (curve.Succeeded())
		CurveFloat = curve.Object;


}

void ACBlockAlpha::BeginPlay()
{
	Super::BeginPlay();
	
	UpdateBlockTimeline(CurveFloat);
}

void ACBlockAlpha::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (Timeline->IsPlaying())
		Timeline->TickTimeline(DeltaTime);

}

void ACBlockAlpha::UpdateBlockTimeline(UCurveFloat * CurveFloat)
{
	Timeline = new FTimeline();//Timeline초기화

	FOnTimelineFloat progress;
	progress.BindUFunction(this, "Progress");

	Timeline->AddInterpFloat(CurveFloat, progress);
	Timeline->SetLooping(false);
	Timeline->SetTimelineLengthMode(TL_LastKeyFrame);
	//TL_LastKeyFrame
	//TL_TimelineLength,
	//Timeline.PlayFromStart();


	FOnTimelineEvent timelineEvent;//
	timelineEvent.BindUFunction(this, "ResetProgress");//리셋
	Timeline->SetTimelineFinishedFunc(timelineEvent);//상황에따라 이벤트 콜

}

void ACBlockAlpha::Progress(float Value)
{
	//float length = Spline->GetSplineLength();
	float playerblock = player->GetBlockAlpha();
	playerblock= CurveFloat->GetFloatValue(Value);
}

void ACBlockAlpha::ResetProgress()
{
}

