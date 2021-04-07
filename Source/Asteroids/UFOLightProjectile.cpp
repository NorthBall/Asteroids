// Fill out your copyright notice in the Description page of Project Settings.

#include "UFOLightProjectile.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "PlayerPawn.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AUFOLightProjectile::AUFOLightProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh0"));
	Sparks = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("VFX0"));		// set up a notification for when this component hits something
	RootComponent = ProjectileMesh;
	Sparks->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AUFOLightProjectile::BeginPlay()
{
	Super::BeginPlay();
	/*ProjectileMesh->OnComponentBeginOverlap.AddDynamic(this, &AUFOLightProjectile::OnBeginOverlap);
	ProjectileMesh->OnComponentHit.AddDynamic(this, &AUFOLightProjectile::OnHit);*/
	
}

void AUFOLightProjectile::OnBeginOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (MainActor != NULL)
	{
		HitActor = Cast<APlayerPawn>(OtherActor);
		if (HitActor != NULL)
		{
			HitActor->TakeDamage(1, FDamageEvent(), MainActor->GetInstigatorController(), this);
			Destroy();
		}
	}
}

void AUFOLightProjectile::OnHit(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{
	Destroy();
}
