// Fill out your copyright notice in the Description page of Project Settings.

#include "MyAsteroid.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "PlayerPawn.h"
#include "Components/SphereComponent.h"
#include "Math/UnrealMathUtility.h"
#include "Engine/World.h"

// Sets default values
AMyAsteroid::AMyAsteroid()
{
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh0"));
	MainCollision = CreateDefaultSubobject<USphereComponent>(TEXT("VFX0"));
	ProjectileMesh->OnComponentBeginOverlap.AddDynamic(this, &AMyAsteroid::OnBeginOverlap);
	ProjectileMesh->OnComponentHit.AddDynamic(this, &AMyAsteroid::OnHit);		// set up a notification for when this component hits something
	RootComponent = MainCollision;
	ProjectileMesh->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AMyAsteroid::BeginPlay()
{
	Super::BeginPlay();
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
		Enemy->Score += pow(2, (Damage<Health)?Damage : Health);
		Health -= Damage;
		if (Health <= 0)
		{
			Destroy();
			return Damage + Health;
		}
		else
		{
			Double();
		}
	}
	else
	{
		Enemy->Score+=pow(2,Health);
		Destroy();
	}
	return Damage;
}

void AMyAsteroid::Double()
{
	ProjectileMovement->Velocity = FRotator(0, 0, FMath::RandRange(0.f, 360.f)).RotateVector(ProjectileMovement->Velocity*1.5);
	SetActorScale3D(GetActorScale3D()*0.7);
	if (World != NULL)
	{
		Twin = World->SpawnActor<AMyAsteroid>(GetClass(), GetActorLocation(), FRotator::ZeroRotator);
		Twin->Enemy = Enemy;
		Twin->ProjectileMovement->Velocity = FRotator(0, 0, FMath::RandRange(0.f, 360.f)).RotateVector(ProjectileMovement->Velocity);
		Twin->SetActorScale3D(GetActorScale3D());//set twin scale equal to first asteroid scale
		Twin->Health = Health;
	}
}

