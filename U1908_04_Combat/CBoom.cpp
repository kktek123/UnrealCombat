
#include "CBoom.h"
#include "Global.h"
#include "CCombatCharacter.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "CEnemy.h"
#include "MyGameProject/CParty.h"
#include "CSpellIndicator.h"

ACBoom::ACBoom()
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
	CollisionComp->BodyInstance.SetCollisionProfileName("Booms");
	CollisionComp->OnComponentHit.AddDynamic(this, &ACBoom::Explosion);		// set up a notification for when this component hits something blocking

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;
	RootComponent = CollisionComp;



	Boom = CreateDefaultSubobject<UStaticMeshComponent>("Boom");
	Boom->CanCharacterStepUpOn = ECB_No;
	//Boom->OnComponentHit.AddDynamic(this, &ACBoom::Explosion);
	FString path = L"StaticMesh'/Game/InfinityBladeAdversaries/Enemy/Enemy_Gruntling_Weapons/Meshes/SM_Gruntling_BombDrop_Internal.SM_Gruntling_BombDrop_Internal'";
	ConstructorHelpers::FObjectFinder<UStaticMesh> mesh(*path);
	if (mesh.Succeeded())
		Boom->SetStaticMesh(mesh.Object);
	Boom->SetupAttachment(CollisionComp);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	//ProjectileMovement->InitialSpeed = 2000.f;
	ProjectileMovement->MaxSpeed = 4000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	//ProjectileMovement->bShouldBounce = true;


	path = L"SoundWave'/Game/DynamicCombatSystem/SFX/WAV/WAV_Explosion02.WAV_Explosion02'";
	ConstructorHelpers::FObjectFinder<USoundBase> shoot(*path);
	if (shoot.Succeeded())
		BoomSound = shoot.Object;


	InitialLifeSpan = 3.0f;
}

void ACBoom::Draw()
{
	bDrawing = true;

	//Boom->SetSimulatePhysics(!bDrawing);
	//Boom->SetEnableGravity(!bDrawing);
	//Boom->SetCollisionEnabled(ECollisionEnabled::NoCollision);

}

void ACBoom::Shoot()
{
	bShooting = true;
	if (bShooting)
	{
		bDrawing = false;
		//CLog::Print(TEXT("Shoot"));
	}

}

void ACBoom::Explosion(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor == this)return;
	//if (GetOwner()->IsA(ACEnemy::StaticClass()))
	//{
	//	if (!OtherActor->IsA(ACEnemy::StaticClass())) 
	//		UGameplayStatics::ApplyDamage(OtherActor, Power, NULL, GetOwner(), NULL);

	//}
	//if (GetOwner()->IsA(ACParty::StaticClass()))
	//{
	//	if (!OtherActor->IsA(ACParty::StaticClass())) 
	//		UGameplayStatics::ApplyDamage(OtherActor, Power, NULL, GetOwner(), NULL);
	//}
	//OtherActor->Destroy();//네트워크
	//UGameplayStatics::ApplyDamage(OtherActor, Power, NULL, GetOwner(), NULL);	//if (OtherActor == GetOwner())return;
	//CLog::Print(TEXT("hit"));
	FVector start = GetActorLocation();
	FVector end = GetActorLocation();
	end.Z += Height;

	FCollisionShape sphere = FCollisionShape::MakeSphere(Radius);
	//DrawDebugSphere(GetWorld(), start, sphere.GetSphereRadius(), 40, FColor::Green, true);
	TArray<FHitResult>hits;
	bool bHit = GetWorld()->SweepMultiByChannel(hits, start, end, FQuat::Identity, ECC_WorldDynamic, sphere);

	if (bHit)
	{
		for (auto& hit : hits)
		{
			USkeletalMeshComponent* mesh = Cast<USkeletalMeshComponent>(hit.GetActor()->GetRootComponent());
			bool b = true;
			//b &= mesh != NULL;
			b &= hit.GetActor()->IsA(ACParty::StaticClass()) == true;
			//b &= hit.GetActor()->GetName().Contains("Wall") == false;
			//b &= hit.GetActor()->GetName().Contains("FirstPersonCharacter") == false;

			if (b)
				UGameplayStatics::ApplyDamage(hit.GetActor(), Power, NULL, this, NULL);
				//mesh->AddRadialImpulse(GetActorLocation(), Radius, mesh->GetMass()*1.25f, ERadialImpulseFalloff::RIF_Constant, true);//발산
			//force 충돌
		}
	}
	//Particle->Activate(true);
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Particle, GetActorLocation(), FRotator());
	UGameplayStatics::PlaySoundAtLocation(this, BoomSound, start, boomsound);
	FlushPersistentDebugLines(GetWorld());
	
	if (SpellIndicator != NULL)
	{
		SpellIndicator->Destroy();
		SpellIndicator = NULL;
	}
	Destroy();
}

void ACBoom::BeginPlay()
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
	FVector start = GetActorLocation();
	start.Z = GetActorLocation().Z - dlPos;
	FVector end = GetActorLocation();
	end.Z += Height;

	FCollisionShape sphere = FCollisionShape::MakeSphere(Radius);
	FActorSpawnParameters ActorSpawnParams;
	//ActorSpawnParams.Owner = this;
	ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	if (fallen)
	{
		//DrawDebugSphere(GetWorld(), start, sphere.GetSphereRadius(), 40, FColor::Green, false,1);
		if (MagicClass != NULL)
			SpellIndicator = GetWorld()->SpawnActor<ACSpellIndicator>(MagicClass, start, GetActorRotation(), ActorSpawnParams);
		boomsound = 0.1f;
	}
	else
	{
		boomsound = 0.75f;
	}
	//GetWorldTimerManager().SetTimer(CountdownTimerHandle, this, , 0.45f, true);

	//Delay
		//FlushPersistentDebugLines(GetWorld());
		//DrawDebugCircle(GetWorld(), start, sphere.GetSphereRadius(), 40, FColor::Green, true, 1, '\000', 0, FVector(0, 1, 0), FVector(1, 0, 0));

}

void ACBoom::Tick(float DeltaTime)
{
	//Super::Tick(DeltaTime);
	//if (bDrawing)
	//{
	//	//CLog::Print(TEXT("Draw"));
	//	SetActorLocationAndRotation(PlayerHolding->GetComponentLocation(), PlayerHolding->GetComponentRotation());
	//}

}

