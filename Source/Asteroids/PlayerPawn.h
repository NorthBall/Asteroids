// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerPawn.generated.h"
class UProjectileMovementComponent;
class UBoxComponent;
class UParticleSystemComponent;
class UAudioComponent;
class USoundBase;
class UCursorWidget;
class UWorld;
class AMyPlayerController;
class AUFOHard;
class AUFOLight;
class AMyAsteroid;
UCLASS()
class ASTEROIDS_API APlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Components
	APlayerPawn();
	~APlayerPawn();
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Meshes")
		UStaticMeshComponent* Body;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Meshes")
		UParticleSystemComponent* Beam;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
		UAudioComponent* MainTheme;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
		UAudioComponent* BeamSound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
		USoundBase* ShootSound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
		UAudioComponent* FailSound;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Movement)
		UProjectileMovementComponent* ProjectileMovement;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Meshes")
		UBoxComponent* MainCollision;
	
	//RealData

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Data")
		int32 Score;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Data")
		int32 Health;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Beam")
		int32 CurrentCharges;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Beam")
		int32 MaxCharges=3;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Beam")
		float reChargeTime;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Beam")
		float MaxChargeTime=5.f;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Beam")
		float TimeToBeam;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Movement")
		FVector SpeedVect;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Movement")
		float MaxSpeed;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Movement")
		float Acceleration;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Shot")
		FVector GunOffset;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Shot")
		float FireRate;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Shot")
		bool CanFire=true;
	FTimerHandle ShootHandle;
	float ShootRate;
	UWorld* Level;
	//states and etc.
	bool IsShooting;
	bool IsBeaming;
	FVector MouseLoc;
	UCursorWidget* PlayerCursor;
	FTimerHandle DeathHandle;
	AMyPlayerController* Controller;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser) override;
	UFUNCTION()
		void AfterDeath();
	UFUNCTION()
		void AfterShoot();
	UFUNCTION()
		void ReplaySound();
	//somefunctions
	void FireShot();
	void Beaming(float Tick);
	UFUNCTION()
	int32 SaveGame();
	void StartBeaming();
	// useless variables
	FVector DeltaSpeed = FVector(0.f);
	FHitResult* SweepHit;
	TSet<UClass*> BeamEnemies;

};
