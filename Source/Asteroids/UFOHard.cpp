// Fill out your copyright notice in the Description page of Project Settings.

#include "UFOHard.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/CapsuleComponent.h"
#include "AIController.h"
#include "PlayerPawn.h"
#include "MyAsteroid.h"


// Sets default values
AUFOHard::AUFOHard()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	Shield = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Shield"));
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AUFOHard::OnBeginOverlap);
	GetCapsuleComponent()->OnComponentEndOverlap.AddDynamic(this, &AUFOHard::OnEndOverlap);
	for (int32 i = 0; i < 6; i++)
	{
		BeamEmitters.Add(CreateDefaultSubobject<UParticleSystemComponent>(FName(TEXT("Emitter"), i)));
		BeamEmitters[i]->SetRelativeLocation(FRotator(0, i * 60, 0).RotateVector(FVector(0, 120, 35)));
		BeamEmitters[i]->ActivateSystem();
		BeamEmitters[i]->SetEmitterEnable(TEXT("Main"), false);
	}
}

// Called when the game starts or when spawned
void AUFOHard::BeginPlay()
{
	Super::BeginPlay();
	bCanBeDamaged = true;
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldDynamic,ECollisionResponse::ECR_Overlap);
}

void AUFOHard::ChaseEnemy(APlayerPawn * Victim)
{
	Enemy = Victim;
	if (Enemy != NULL)
	{
		if (Cast<AAIController>(GetController()) != NULL) Cast<AAIController>(GetController())->MoveToActor(Enemy);
	}
}

void AUFOHard::PowerOff(AActor* IgnoredActor)
{
	TSet<AActor*> OverlappedActors;
	GetOverlappingActors(OverlappedActors, AMyAsteroid::StaticClass());
	if (IgnoredActor!=NULL) OverlappedActors.Remove(IgnoredActor);
	if (OverlappedActors.Num() == 0)
	{
		bCanBeDamaged = true;
		ShieldOn = false;
		Shield->SetVisibility(false);
		for (UParticleSystemComponent* Emit : BeamEmitters)
		{
			Emit->SetEmitterEnable(TEXT("Main"), false);
		}
	}
}

void AUFOHard::PowerOn()
{
	bCanBeDamaged = false;
	ShieldOn = true;
	Shield->SetVisibility(true);
	for (UParticleSystemComponent* Emit : BeamEmitters)
	{
		Emit->SetEmitterEnable(TEXT("Main"), true);
	}
}

float AUFOHard::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser)
{
	if (Enemy!=NULL) Enemy->Score++;
	Destroy();
	return Damage;
}

void AUFOHard::OnBeginOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if(!ShieldOn)	if (OtherActor->GetClass() == AMyAsteroid::StaticClass())
	{
		PowerOn();
	}
	else
	{
		if (OtherActor->GetClass() == APlayerPawn::StaticClass())
		{
			OtherActor->TakeDamage(1, FDamageEvent(), GetInstigatorController(), this);
		}
	}
}

void AUFOHard::OnEndOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	if (Cast<AMyAsteroid>(OtherActor) != NULL && ShieldOn)
	{
		PowerOff(Cast<AMyAsteroid>(OtherActor));
	}
}
