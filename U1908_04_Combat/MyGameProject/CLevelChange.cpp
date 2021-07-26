#include "CLevelChange.h"
#include "Engine/Classes/Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

ACLevelChange::ACLevelChange()
{
	PrimaryActorTick.bCanEverTick = true;

	TransferVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("TransferVelume"));
	RootComponent = TransferVolume;
	TransferVolume->SetCollisionProfileName(TEXT("OverlapOnlyPawn"));
}

void ACLevelChange::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACLevelChange::NotifyActorBeginOverlap(AActor * OtherActor)
{
	APawn* Pawn = Cast<APawn>(OtherActor);
	if (Pawn != nullptr)
	{
		UGameplayStatics::OpenLevel(this, LevelName);
	}
}

void ACLevelChange::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

