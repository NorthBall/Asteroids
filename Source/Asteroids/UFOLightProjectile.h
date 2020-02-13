// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UFOLightProjectile.generated.h"

class UProjectileMovementComponent;
class UParticleSystemComponent;

UCLASS()
class ASTEROIDS_API AUFOLightProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AUFOLightProjectile();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Meshes")
		UStaticMeshComponent* ProjectileMesh;

	/** Projectile movement component */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Movement)
		UProjectileMovementComponent* ProjectileMovement;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Support")
		AActor* HitActor;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Support")
		APawn* MainActor;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Meshes")
		UParticleSystemComponent* Sparks;
public:
	// Called every frame
	virtual void BeginPlay() override;
	UFUNCTION()
		void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
	
};
