// Fill out your copyright notice in the Description page of Project Settings.

#include "UFOLight.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "AIController.h"
#include "PlayerPawn.h"
#include "Engine/World.h"
#include "UFOLightProjectile.h"

// Sets default values
AUFOLight::AUFOLight()
{
	//BonesName.Add(TEXT("Bone1")); BonesName.Add(TEXT("Bone2")); BonesName.Add(TEXT("Bone3")); BonesName.Add(TEXT("Bone4")); BonesName.Add(TEXT("Bone5")); BonesName.Add(TEXT("Bone6"));
}

// Called when the game starts or when spawned
void AUFOLight::BeginPlay()
{
	Super::BeginPlay();
	Level = GetWorld();
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AUFOLight::OnBeginOverlap);
}

float AUFOLight::TakeDamage(float Damage, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	if (Enemy!=NULL) Enemy->Score+=2;
	Destroy();
	return Damage;
}

void AUFOLight::OnBeginOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (Cast<APlayerPawn>(OtherActor) != NULL)
	{
		Enemy->Score += 100;
		Destroy();
	}
}

void AUFOLight::Shoot()
{
	if (Enemy != NULL&& Level!=NULL)
	{
		FVector ELoc = Enemy->GetActorLocation();
		FVector TLoc=FindBestTurret(ELoc);
		SpawnedProjectile=Level->SpawnActor<AUFOLightProjectile>(ClassOfProjectile, TLoc, (ELoc - TLoc).GetSafeNormal2D().ToOrientationRotator());
		if (SpawnedProjectile != NULL) SpawnedProjectile->MainActor = this;
	}
}

void AUFOLight::Init(APlayerPawn* Victim)
{
	Enemy = Victim;
	InitBlackBoard();
}

FVector AUFOLight::FindBestTurret(FVector ELocation)
{
	FVector Result(GetMesh()->GetSocketLocation(BonesName[0]));
	FVector IRes(Result);
	float IDist;
	float Distance=FVector::Dist2D(IRes,ELocation);
	for (int32 i = 1; i < 6; i++)
	{
		IRes = GetMesh()->GetSocketLocation(BonesName[i]);
		IDist = FVector::Dist2D(IRes, ELocation);
		if (IDist < Distance)
		{
			Distance = IDist;
			Result = IRes;
		}
	}
	return Result;
	
}


