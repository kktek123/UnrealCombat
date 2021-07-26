#include "CSword.h"
#include "Global.h"

ACSword::ACSword()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>("Mesh");
	RootComponent = Mesh;

	Capsule = CreateDefaultSubobject<UCapsuleComponent>("Capsule");
	Capsule->SetupAttachment(Mesh);


	FString path = L"SkeletalMesh'/Game/Character/Sword/SK_Straight_Sword.SK_Straight_Sword'";
	ConstructorHelpers::FObjectFinder<USkeletalMesh> mesh(*path);
	if (mesh.Succeeded())
		Mesh->SkeletalMesh = mesh.Object;

	Capsule->SetRelativeLocation(FVector(-10, -120, 0));
	Capsule->SetRelativeRotation(FRotator(0, 0, 90));
	Capsule->SetCapsuleRadius(15);
	Capsule->SetCapsuleHalfHeight(200);
}

void ACSword::BeginPlay()
{
	Super::BeginPlay();
	
	Capsule->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	Capsule->OnComponentBeginOverlap.AddDynamic(this, &ACSword::OnBegin);
	Capsule->OnComponentEndOverlap.AddDynamic(this, &ACSword::OnEnd);
}

void ACSword::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACSword::OnBegin(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor == this) return;
	if (OtherActor == GetOwner()) return;

	//OtherActor->Destroy();

	UGameplayStatics::ApplyDamage(OtherActor, Power, NULL, GetOwner(), NULL);
}

void ACSword::OnEnd(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{

}