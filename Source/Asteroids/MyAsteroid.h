// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "MyAsteroid.generated.h"

class UProjectileMovementComponent;
class USphereComponent;
class APlayerPawn;

UCLASS()
class ASTEROIDS_API AMyAsteroid : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyAsteroid();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Meshes")
		UStaticMeshComponent* ProjectileMesh;

	/** Projectile movement component */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Movement)
		UProjectileMovementComponent* ProjectileMovement;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Support")
		AActor* HitActor;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Support")
		APlayerPawn* Enemy;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Support")
		int32 Health;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Meshes")
		USphereComponent* MainCollision;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser) override;
	//support
	void Double(int32 TimesToRepeat);

	AMyAsteroid* Twin;
	UWorld* World;

	UFUNCTION()
		void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
};
