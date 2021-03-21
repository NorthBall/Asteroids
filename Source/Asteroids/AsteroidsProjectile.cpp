// Copyright 1998-2018 Epic Games, Inc. All Rights Reserve

#include "AsteroidsProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"

AAsteroidsProjectile::AAsteroidsProjectile() 
{
	// Static reference to the mesh to use for the projectile
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ProjectileMeshAsset(TEXT("/Game/TwinStick/Meshes/TwinStickProjectile.TwinStickProjectile"));

	// Create mesh component for the projectile sphere
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh0"));
	ProjectileMesh->SetStaticMesh(ProjectileMeshAsset.Object);
	ProjectileMesh->SetupAttachment(RootComponent);
	ProjectileMesh->BodyInstance.SetCollisionProfileName("Projectile");
	//ProjectileMesh->BodyInstance.
	UE_LOG(LogTemp, Warning, TEXT("%d Why"), (3>2)?4:5);
	ProjectileMesh->BodyInstance.SetResponseToChannel(ECollisionChannel::ECC_GameTraceChannel1, ECollisionResponse::ECR_Ignore);
	ProjectileMesh->OnComponentHit.AddDynamic(this, &AAsteroidsProjectile::OnHit);		// set up a notification for when this component hits something
	RootComponent = ProjectileMesh;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement0"));
	ProjectileMovement->UpdatedComponent = ProjectileMesh;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = false;
	ProjectileMovement->ProjectileGravityScale = 0.f; // No gravity

	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;
}

void AAsteroidsProjectile::BeginPlay()
{
	UE_LOG(LogTemp, Warning, TEXT("Object type %d  %d"),ProjectileMesh->BodyInstance.GetObjectType(), ECollisionChannel::ECC_GameTraceChannel1);
	//ProjectileMesh->BodyInstance.SetResponseToChannel(ECollisionChannel::ECC_GameTraceChannel1, ECollisionResponse::ECR_Ignore);
	if (ProjectileMesh->GetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel1) == ECollisionResponse::ECR_Ignore)
	{
		UE_LOG(LogTemp, Warning, TEXT("Changed"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("NotChanged"));
	}
	
	Super::BeginPlay();
	
}

void AAsteroidsProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Only add impulse and destroy projectile if we hit a physics
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL) && OtherComp->IsSimulatingPhysics())
	{
		OtherComp->AddImpulseAtLocation(GetVelocity() * 20.0f, GetActorLocation());
	}

	Destroy();
}