#include "CFireball.h"
#include "Global.h"
#include "CCombatCharacter.h"
#include "CEnemy.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
ACFireball::ACFireball()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ConstructorHelpers::FObjectFinder<UParticleSystem>particle
	(
		L"ParticleSystem'/Game/DynamicCombatSystem/VFX/P_FireballHit.P_FireballHit'"
	);
	if (particle.Succeeded())
		Particle = particle.Object;
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Fireball");
	CollisionComp->OnComponentHit.AddDynamic(this, &ACFireball::Explosion);		// set up a notification for when this component hits something blocking

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;
	RootComponent = CollisionComp;

	Fireball = CreateDefaultSubobject<UParticleSystemComponent>("Fireball");
	FString path = L"ParticleSystem'/Game/DynamicCombatSystem/VFX/P_Fireball.P_Fireball'";
	ConstructorHelpers::FObjectFinder<UParticleSystem> fireball(*path);
	if (fireball.Succeeded())
		Fireball->SetTemplate(fireball.Object);
	Fireball->SetupAttachment(CollisionComp);

	path = L"SoundCue'/Game/DynamicCombatSystem/SFX/CUE/CUE_FireballHit.CUE_FireballHit'";
	ConstructorHelpers::FObjectFinder<USoundBase> shoot(*path);
	if (shoot.Succeeded())
		BoomSound = shoot.Object;


	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;
	InitialLifeSpan = 3.0f;

}

// Called when the game starts or when spawned
void ACFireball::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACFireball::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACFireball::Charge()
{
}

void ACFireball::Shoot()
{
}

void ACFireball::Explosion(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{
	if (OtherActor == this) return;
	//CLog::Print(TEXT("hit"));
	//if (this->IsA(ACCombatCharacter::StaticClass()))
	//	if (OtherActor->IsA(ACCombatCharacter::StaticClass()))
	//		return;
	//if (this->IsA(ACEnemy::StaticClass()))
	//	if (OtherActor->IsA(ACEnemy::StaticClass()))
	//		return;
	UGameplayStatics::ApplyDamage(OtherActor, 10, NULL, this, NULL);
	FVector start = GetActorLocation();
	FVector end = GetActorLocation();
	end.Z += Height;

	FCollisionShape sphere = FCollisionShape::MakeSphere(Radius);
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Particle, GetActorLocation(), FRotator());
	UGameplayStatics::PlaySoundAtLocation(this, BoomSound, start);

	Destroy();

}

