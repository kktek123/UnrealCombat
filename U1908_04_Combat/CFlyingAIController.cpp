// Fill out your copyright notice in the Description page of Project Settings.


#include "CFlyingAIController.h"
#include "Global.h"
#include "NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "GameFramework/Character.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "CEnemy.h"

ACFlyingAIController::ACFlyingAIController()
{
	FString path = L"CurveFloat'/Game/MyGameProjection/Alpha/BlockAlpha1.BlockAlpha1'";
	ConstructorHelpers::FObjectFinder<UCurveFloat> curve(*path);
	if (curve.Succeeded())
		CurveFloat = curve.Object;

}

void ACFlyingAIController::BeginPlay()
{
	Super::BeginPlay();

}

void ACFlyingAIController::OnPossess(APawn * InPawn)
{
	Super::OnPossess(InPawn);
	PossesedAI = Cast<ACEnemy>(InPawn);
	//PossesedAI->SetActorLocation(FVector(0,0,0));

	FindLocation();
}

void ACFlyingAIController::OnUnPossess()
{
	Super::OnUnPossess();

}

void ACFlyingAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (Timeline.IsPlaying())
		Timeline.TickTimeline(DeltaTime);
}

void ACFlyingAIController::OnSensingTarget(AActor * Actor, FAIStimulus Stimulus)
{
}

void ACFlyingAIController::FindLocation()
{
	CLog::Print(TEXT("FindLocation"));

	//MoveToLocation();
	ML = PossesedAI->GetActorLocation();
	NL = UKismetMathLibrary::RandomPointInBoundingBox(ML, FVector(500, 500, 500));
	UpdateFlightTimeline(CurveFloat);
	Timeline.PlayFromStart();

}

void ACFlyingAIController::Progress()
{
	//NewLocation = FMath::Lerp(ML, NL, Timeline.GetPlayRate());
	PossesedAI->SetActorLocation(NewLocation);
	CLog::Print(TEXT("Progress"));
}

void ACFlyingAIController::Progressfloat(float Value)
{
	NewLocation = FMath::Lerp(ML, NL, Value);
	//PossesedAI->SetActorLocation(NewLocation);
	CLog::Print(TEXT("Progressfloat"));
}

void ACFlyingAIController::ResetProgress()
{
	FindLocation();
	CLog::Print(TEXT("ResetProgress"));

}

void ACFlyingAIController::UpdateFlightTimeline(UCurveFloat * CurveFloat)
{
	//Timeline = FTimeline();//Timeline초기화


	//Timeline.SetFloatCurve(CurveFloat, FName("timeline"));
	progress.BindUFunction(this, "Progress");
	progressfloat.BindUFunction(this, "Progressfloat");
	timelineEvent.BindUFunction(this, FName{ TEXT("ResetProgress") });//리셋
	Timeline.AddInterpFloat(CurveFloat, progressfloat);
	Timeline.SetLooping(false);
	Timeline.SetTimelineLengthMode(TL_TimelineLength);
	Timeline.SetTimelineLength(2);
	Timeline.SetTimelinePostUpdateFunc(progress);//상황에따라 이벤트 콜

	//
	Timeline.SetTimelineFinishedFunc(timelineEvent);//상황에따라 이벤트 콜
}


