// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "UFOHard.generated.h"

class UStaticMeshComponent;
class UParticleSystemComponent;
class APlayerPawn;
class AAIController;


UCLASS()
class ASTEROIDS_API AUFOHard : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AUFOHard();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Meshes")
		UStaticMeshComponent* Body;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Meshes")
		UStaticMeshComponent* Shield;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Meshes")
		TArray<UParticleSystemComponent*> BeamEmitters;

	APlayerPawn* Enemy;
	bool ShieldOn;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	//UFUNCTION()
	void ChaseEnemy(APlayerPawn* Victim);
	void PowerOff(AActor* IgnoredActor=NULL);
	void PowerOn();
	UFUNCTION()
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser) override;
	UFUNCTION()
		void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	//some support variable
	AAIController* TrueController;//Controller of Pawn with right class
};
