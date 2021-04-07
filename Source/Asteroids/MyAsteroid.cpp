// Fill out your copyright notice in the Description page of Project Settings.

#include "MyAsteroid.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "PlayerPawn.h"
#include "Components/SphereComponent.h"
#include "Math/UnrealMathUtility.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Engine/World.h"

// Sets default values
AMyAsteroid::AMyAsteroid()
{
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh0"));
	MainCollision = CreateDefaultSubobject<USphereComponent>(TEXT("VFX0"));		//for physic interaction
	RootComponent = MainCollision;
	ProjectileMesh->SetupAttachment(RootComponent);
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement0"));
	ProjectileMovement->UpdatedComponent = RootComponent;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = false;
	ProjectileMovement->ProjectileGravityScale = 0.f;

}

// Called when the game starts or when spawned
void AMyAsteroid::BeginPlay()
{
	Super::BeginPlay();
	/*if (MainCollision != NULL)
	{
		MainCollision->OnComponentBeginOverlap.AddDynamic(this, &AMyAsteroid::OnBeginOverlap); //for gameplay interactions
		MainCollision->OnComponentHit.AddDynamic(this, &AMyAsteroid::OnHit);
	}*/
	World = GetWorld();
}

void AMyAsteroid::OnBeginOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	HitActor = Cast<APlayerPawn>(OtherActor);
	if (HitActor != NULL)
	{
		HitActor->TakeDamage(1, FDamageEvent(), GetInstigatorController(), this);
		Destroy();
	}
}

void AMyAsteroid::OnHit(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{
	Destroy();
}

float AMyAsteroid::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser)
{
	if (Damage > 0)
	{
		//damage-driven weapon
		Enemy->Score += pow(2, (Damage<Health)?Damage : Health);
		Health -= Damage;
		if (Health <= 0)
		{
			Destroy();
			return Damage + Health;
		}
		else
		{
			Double(Damage);
		}
	}
	else
	{
		//ultimate weapon like Laser Beam
		Enemy->Score+=pow(2,Health);
		Destroy();
	}
	return Damage;
}

void AMyAsteroid::Double(int32 TimesToRepeat )
{
	//function to crush asteroid to 2 small parts
	ProjectileMovement->Velocity = FRotator(0, 0, FMath::RandRange(0.f, 360.f)).RotateVector(ProjectileMovement->Velocity*1.5);
	SetActorScale3D(GetActorScale3D()*pow(0.7,TimesToRepeat));
	if (World != NULL)
	{
		TimesToRepeat = round(pow(2, TimesToRepeat));
		for (int32 i = 1; i < TimesToRepeat; i++)
		{
			Twin = World->SpawnActor<AMyAsteroid>(GetClass(), GetActorLocation(), FRotator::ZeroRotator);
			Twin->Enemy = Enemy;
			Twin->ProjectileMovement->Velocity = FRotator(0, 0, FMath::RandRange(0.f, 360.f)).RotateVector(ProjectileMovement->Velocity);
			Twin->SetActorScale3D(GetActorScale3D());//set twin scale equal to first asteroid scale
			Twin->Health = Health;
		}
	}
}

