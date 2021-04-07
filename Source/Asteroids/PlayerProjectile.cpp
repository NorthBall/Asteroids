// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerProjectile.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "UFOHard.h"
#include "UFOLight.h"
#include "MyAsteroid.h"
#include "Engine/StaticMesh.h"

// Sets default values
APlayerProjectile::APlayerProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh0"));
	// set up a notification for when this component hits something
	RootComponent = ProjectileMesh;
	Enemies = { AUFOHard::StaticClass(),AMyAsteroid::StaticClass(),AUFOLight::StaticClass() };
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement0"));
	ProjectileMovement->UpdatedComponent = RootComponent;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = false;
	ProjectileMovement->ProjectileGravityScale = 0.f;
}

// Called when the game starts or when spawned
void APlayerProjectile::BeginPlay()
{
	Super::BeginPlay(); 
	if (ProjectileMesh != NULL)
	{
		ProjectileMesh->OnComponentBeginOverlap.AddDynamic(this, &APlayerProjectile::OnBeginOverlap);
		ProjectileMesh->OnComponentHit.AddDynamic(this, &APlayerProjectile::OnHit);
	}
}

void APlayerProjectile::OnBeginOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (MainActor != NULL&&OtherActor!=NULL)
	{
		if (Enemies.Contains(OtherActor->GetClass()))
		{
			OtherActor->TakeDamage(1, FDamageEvent(), MainActor->GetInstigatorController(), this);
			Destroy();
		}
		/*HitActor = Cast<AUFOHard>(OtherActor);
		if (HitActor == NULL) HitActor = Cast<AUFOLight>(OtherActor);
		if (HitActor == NULL) HitActor = Cast<AMyAsteroid>(OtherActor);
		if (HitActor != NULL)
		{
			HitActor->TakeDamage(1, FDamageEvent(), MainActor->GetInstigatorController(), this);
			Destroy();
		}*/
	}
}

void APlayerProjectile::OnHit(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{
	Destroy();
}

