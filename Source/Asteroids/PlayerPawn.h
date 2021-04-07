// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "UFOHard.h"
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
class APlayerProjectile;
UCLASS()
class ASTEROIDS_API APlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Components
	APlayerPawn();
	~APlayerPawn();
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Init/Meshes")
		UStaticMeshComponent* Body;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Init/Meshes")
		UParticleSystemComponent* Beam;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Init/Audio")
		UAudioComponent* MainTheme;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Init/Audio")
		UAudioComponent* BeamSound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Init|Audio")
		USoundBase* ShootSound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Init/Audio")
		UAudioComponent* FailSound; //zero Laser Beam charges 
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Movement)
		UProjectileMovementComponent* ProjectileMovement;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Init/Collision")
		UBoxComponent* MainCollision;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Init")
		TSubclassOf<APlayerProjectile> ProjectileClass;
	
	//RealData

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Data")
		int32 Score;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Data")
		int32 Health=3;
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
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Beam")
		float MaxBeamTime=1.f;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Movement")
		FVector SpeedVect;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Movement")
		float MaxSpeed=2000;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Movement")
		float Acceleration=700;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Shot")
		FVector GunOffset;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Shot")
		float FireRate=.1f;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Shot")
		bool CanFire=true;
	FTimerHandle ShootHandle;
	float ShootRate;
	UWorld* Level;
	//states and etc.
	bool IsShooting=false;
	bool IsBeaming=false;
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
	FHitResult TempHit;
	TSet<UClass*> BeamEnemies;
	UFUNCTION(BlueprintImplementableEvent)
		FHitResult DebugHelper(FVector Offset);

};
