// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "UFOLight.generated.h"

class UStaticMeshComponent;
class APlayerPawn;
class UWorld;

UCLASS()
class ASTEROIDS_API AUFOLight : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AUFOLight();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Meshes")
		UStaticMeshComponent* Body;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Meshes")
		TArray<FName> BonesName = {TEXT("Bone1"),TEXT("Bone2") ,TEXT("Bone3") ,TEXT("Bone4") ,TEXT("Bone5") ,TEXT("Bone6") };
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	APlayerPawn* Enemy;
	UWorld* Level;

	UFUNCTION()
		virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser) override;
	UFUNCTION()
		void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION(BlueprintCallable)
		void Shoot();
	FVector FindBestTurret(FVector ELocation);

	
	
};
