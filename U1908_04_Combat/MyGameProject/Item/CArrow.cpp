
#include "CArrow.h"
#include "Global.h"
#include "CCombatCharacter.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "CImpactedArrow.h"

ACArrow::ACArrow()
{
	PrimaryActorTick.bCanEverTick = true;

	ConstructorHelpers::FObjectFinder<UParticleSystem>particle
	(
		L"ParticleSystem'/Game/DynamicCombatSystem/VFX/P_Explosion.P_Explosion'"
	);
	if (particle.Succeeded())
		Particle = particle.Object;
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Arrows");
	CollisionComp->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel1);
	//CollisionComp->OnComponentHit.AddDynamic(this, &ACArrow::OnHit);		// set up a notification for when this component hits something blocking
	CollisionComp->OnComponentHit.AddDynamic(this, &ACArrow::Explosion);		// set up a notification for when this component hits something blocking

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;
	
	RootComponent = CollisionComp;
	//CollisionComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	


	Arrow = CreateDefaultSubobject<UStaticMeshComponent>("Arrow");
	//Arrow->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Arrow->CanCharacterStepUpOn = ECB_No;
	//Arrow->OnComponentHit.AddDynamic(this, &ACArrow::OnHit);
	//Arrow->OnComponentHit.AddDynamic(this, &ACArrow::Explosion);
	FString path = L"StaticMesh'/Game/DynamicCombatSystem/Meshes/SM_ExplosiveArrow.SM_ExplosiveArrow'";
	ConstructorHelpers::FObjectFinder<UStaticMesh> mesh(*path);
	if (mesh.Succeeded())
		Arrow->SetStaticMesh(mesh.Object);
	Arrow->SetupAttachment(CollisionComp);
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 0;
	ProjectileMovement->MaxSpeed = 4000.f;
	ProjectileMovement->bShouldBounce = true;
	ProjectileMovement->bRotationFollowsVelocity = false;
	ProjectileMovement->bInitialVelocityInLocalSpace = false;
	ProjectileMovement->ProjectileGravityScale = 0;
	//ProjectileMovement->bAutoActivate = false;

}

void ACArrow::Draw()
{
	bDrawing = true;

	//Arrow->SetSimulatePhysics(!bDrawing);
	//Arrow->SetEnableGravity(!bDrawing);
	//Arrow->SetCollisionEnabled(ECollisionEnabled::NoCollision);

}

void ACArrow::Shoot()
{
	//bShooting = true;
	if (bShooting)
	{
		bDrawing = false;
		//CLog::Print(TEXT("Shoot"));
		//Destroy();
		//Arrow->SetSimulatePhysics(!bDrawing);
		//Arrow->SetEnableGravity(!bDrawing);
		//Arrow->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		//ProjectileMovement->bRotationFollowsVelocity = true;
		//ProjectileMovement->bShouldBounce = true;

		//ProjectileMovement->UpdatedComponent = CollisionComp;
		//ProjectileMovement->InitialSpeed = 3000.f;
		//ProjectileMovement->MaxSpeed = 3000.f;
		//ProjectileMovement->bRotationFollowsVelocity = true;
		//ProjectileMovement->bShouldBounce = true;

		//FVector forward = PlayerCamera->GetForwardVector();
		//Arrow->AddForce(forward * 1e+5f * Arrow->GetMass());
		//InitialLifeSpan = 3.0f;
	}

}

void ACArrow::Explosion(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor == this)return;
	//UGameplayStatics::ApplyDamage(OtherActor, 10, NULL, this, NULL);
	//if (OtherActor == GetOwner())return;
	//CLog::Print(TEXT("hit"));
	//FVector start = GetActorLocation();
	//FVector end = GetActorLocation();
	//end.Z += Height;

	//FCollisionShape sphere = FCollisionShape::MakeSphere(Radius);

	//TArray<FHitResult>hits;
	//bool bHit = GetWorld()->SweepMultiByChannel(hits, start, end, FQuat::Identity, ECC_WorldDynamic, sphere);

	//if (bHit)
	//{
	//	for (auto& hit : hits)
	//	{
	//		UStaticMeshComponent* mesh = Cast<UStaticMeshComponent>(hit.GetActor()->GetRootComponent());
	//		bool b = true;
	//		b &= mesh != NULL;
	//		b &= hit.GetActor()->GetName().Contains("Floor") == false;
	//		b &= hit.GetActor()->GetName().Contains("Wall") == false;
	//		//b &= hit.GetActor()->GetName().Contains("FirstPersonCharacter") == false;

	//		if (b)
	//			mesh->AddRadialImpulse(GetActorLocation(), Radius, mesh->GetMass()*1.25f, ERadialImpulseFalloff::RIF_Constant, true);//발산
	//		//force 충돌
	//	}
	//}
	//Particle->Activate(true);
	//UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Particle, GetActorLocation(), FRotator());
	//Destroy();

	//CLog::Print(TEXT("hit"));
	bool BH;
	bool IO;
	float Time;
	float Distance;
	FVector HitLocation, IP, Normal, INormal, TS, TE;
	UPhysicalMaterial *PM;
	AActor* HitActor;
	UPrimitiveComponent* HitComponent;
	FName HitBoneName;
	int32 HI, FI;

	UGameplayStatics::BreakHitResult(Hit, BH, IO, Time, Distance, HitLocation, IP, Normal, INormal, PM, HitActor, HitComponent, HitBoneName, HI, FI, TS, TE);
	SpawnImpactedArrow(HitComponent, HitBoneName, HitActor, HitLocation);

	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL) && OtherComp->IsSimulatingPhysics())
	{
		


	}
}

void ACArrow::OnHit(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{//안쓴다.
	if (OtherActor == this)return;
	UGameplayStatics::ApplyDamage(OtherActor, 10, NULL, this, NULL);
	//CLog::Print(TEXT("hit"));
	bool BH;
	bool IO;
	float Time;
	float Distance;
	FVector HitLocation,IP,Normal,INormal,TS,TE;
	UPhysicalMaterial *PM;
	AActor* HitActor;
	UPrimitiveComponent* HitComponent;
	FName HitBoneName;
	int32 HI, FI;



	UGameplayStatics::BreakHitResult(Hit,BH,IO,Time,Distance, HitLocation,IP,Normal, INormal, PM, HitActor, HitComponent, HitBoneName,HI,FI,TS,TE);
	SpawnImpactedArrow(HitComponent, HitBoneName, HitActor, HitLocation);
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Particle, GetActorLocation(), FRotator());
	Destroy();
	//SpawnImpactedArrow(OtherComp, HitBoneName, OtherActor, GetActorLocation());

}

void ACArrow::SpawnImpactedArrow(USceneComponent * Component, FName SocketName, AActor * actor, FVector Vector)
{

	ProjectileMovement->StopMovementImmediately();
	FActorSpawnParameters ActorSpawnParams;
	ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	FTransform SpawnTransform = UKismetMathLibrary::MakeTransform(Vector, GetActorRotation(), GetActorScale3D());
	
	//ImpactedArrow = GetWorld()->SpawnActor<ACImpactedArrow>(ImpactedArrowClass, SpawnTransform, ActorSpawnParams);
	//ImpactedArrow->ImpactedArrow->SetStaticMesh(Arrow->GetStaticMesh());

	CollisionComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	this->AttachToActor(actor, FAttachmentTransformRules::KeepWorldTransform, SocketName);
	GetWorldTimerManager().SetTimer(Destroytime, this, &ACArrow::DestroyArrow, 3.0f, false);

	bShooting = false;
	bHit = false;
	//ImpactedArrow->AttachToActor(actor, FAttachmentTransformRules::KeepWorldTransform, SocketName);

}

void ACArrow::OnShoot(FVector target)
{
	ProjectileMovement->SetVelocityInLocalSpace(target+FVector(4000, 0, 0));
	CollisionComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);	
	bShooting = true;
	
	//

	//ProjectileMovement->bAutoActivate = true;
}

void ACArrow::DestroyArrow()
{
	Destroy();
}

void ACArrow::BeginPlay()
{
	Super::BeginPlay();

	Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);


	CombatPlayer = Cast<ACCombatCharacter>(Player);
	TArray<USceneComponent *> components;
	CombatPlayer->GetComponents(components);

	for (USceneComponent* comp : components)
	{
		if (comp->IsA(UCameraComponent::StaticClass()) == true)
			PlayerCamera = Cast<UCameraComponent>(comp);

		if (comp->GetName() == AttachName)
			PlayerHolding = comp;
	}


}

void ACArrow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//if (bDrawing)
	//{
	//	//CLog::Print(TEXT("Draw"));
	//	SetActorLocationAndRotation(PlayerHolding->GetComponentLocation(), PlayerHolding->GetComponentRotation());
	//}
	if (bShooting)
	{
		//bHit = UKismetSystemLibrary::LineTraceSingle(GetWorld(), GetActorLocation() + FQuat(GetActorRotation()).GetForwardVector() * 10, GetActorLocation() + FQuat(GetActorRotation()).GetForwardVector()*1000, ETraceTypeQuery::TraceTypeQuery3, false, AtI, EDrawDebugTrace::Persistent, HitResult,true);
		bHit = UKismetSystemLibrary::SphereTraceSingle(GetWorld(), GetActorLocation(), GetActorLocation() + FQuat(GetActorRotation()).GetForwardVector() * 5,5, ETraceTypeQuery::TraceTypeQuery3, false, AtI, EDrawDebugTrace::ForOneFrame, HitResult, true);
		if (HitResult.IsValidBlockingHit())
		{
		}
		if (bHit)
		{
			UGameplayStatics::ApplyDamage(HitResult.GetActor(), 10, NULL, this, NULL);
			SpawnImpactedArrow(HitResult.GetComponent(), HitResult.BoneName, HitResult.GetActor(), HitResult.Location);
		}

	}
}

