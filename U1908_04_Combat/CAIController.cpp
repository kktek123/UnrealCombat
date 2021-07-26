#include "CAIController.h"
#include "Global.h"
#include "NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "GameFramework/Character.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "CEnemy.h"

ACAIController::ACAIController()
{
	SetGenericTeamId(FGenericTeamId(1));

	FString path = L"";
	path = L"BlackboardData'/Game/Blueprints/BB.BB'";
	
	static ConstructorHelpers::FObjectFinder<UBlackboardData> bb(*path);
	if (bb.Succeeded())
		BB = bb.Object;

	//path = L"BehaviorTree'/Game/MyPortpol/BT1.BT1'";
	//path = L"BehaviorTree'/Game/Blueprints/BT.BT'";
	//static ConstructorHelpers::FObjectFinder<UBehaviorTree> bt(*path);
	//if (bt.Succeeded())
	//	BT = bt.Object;

	Perception = CreateDefaultSubobject<UAIPerceptionComponent>("Perception");

	Sight = CreateDefaultSubobject<UAISenseConfig_Sight>("Sight");
	Sight->SightRadius = 1000.0f;
	Sight->LoseSightRadius = 1200.0f;
	Sight->PeripheralVisionAngleDegrees = 180.0f;
	Sight->SetMaxAge(5.0f);

	Sight->DetectionByAffiliation.bDetectEnemies = true;
	Sight->DetectionByAffiliation.bDetectFriendlies = false;
	Sight->DetectionByAffiliation.bDetectNeutrals = false;

	Perception->ConfigureSense(*Sight);
	Perception->SetDominantSense(*Sight->GetSenseImplementation());
}

void ACAIController::BeginPlay()
{
	Super::BeginPlay();

	Perception->OnTargetPerceptionUpdated.AddDynamic(this, &ACAIController::OnSensingTarget);
}

void ACAIController::OnPossess(APawn * InPawn)
{
	Super::OnPossess(InPawn);

	if (UseBlackboard(BB, Blackboard))
	{
		Blackboard->SetValueAsVector("Home", InPawn->GetActorLocation());
		PossesedAI = Cast<ACEnemy>(InPawn);
		RunBehaviorTree(PossesedAI->GetBT());
	}
}

void ACAIController::OnUnPossess()
{
	Super::OnUnPossess();

}

void ACAIController::OnSensingTarget(AActor * Actor, FAIStimulus Stimulus)
{
	if (Stimulus.WasSuccessfullySensed())
	{
		//FString str = Actor->GetName() + FString(L" Success!");
		//CLog::Print(str, 10.0f, FColor::Red, 10);

		Blackboard->SetValueAsObject("Target", Actor);
		GetTarget = Actor;
	}
	//else
	//{
	//	//CLog::Print(L"Failed", 10.0f, FColor::Red, 10);
	//	Blackboard->SetValueAsObject("Target", NULL);
	//	GetTarget = NULL;
	//}
	
}

//void ACAIController::OnPossess(APawn * InPawn)
//{
//	Super::OnPossess(InPawn);
//
//	FTimerManager& timer = GetWorld()->GetTimerManager();
//	timer.SetTimer(RepeatTimerHandle, this, &ACAIController::OnRepeat, RepeatInterval, true, 0.0f);
//}
//
//void ACAIController::OnUnPossess()
//{
//	Super::OnUnPossess();
//
//	FTimerManager& timer = GetWorld()->GetTimerManager();
//	timer.ClearTimer(RepeatTimerHandle);
//}
//
//void ACAIController::OnRepeat()
//{
//	APawn* pawn = GetPawn();
//
//	UNavigationSystemV1* navSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());
//	verifyf(navSystem != NULL, L"navSystem != NULL");
//
//	FNavLocation location;
//	if (navSystem->GetRandomPointInNavigableRadius(pawn->GetActorLocation(), 500.0f, location))
//		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, location);
//}