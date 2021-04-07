// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "PlayerPawn.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/BoxComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"
#include "CursorWidget.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Engine/EngineTypes.h"
#include "EngineUtils.h"
#include "UFOHard.h"
#include "UFOLight.h"
#include "MyAsteroid.h"
#include "MyHUD.h"
#include "MyPlayerController.h"
#include "ScoreLine.h"
#include "PlayerProjectile.h"
#include "Misc/CoreMiscDefines.h"
#include "UObject/Class.h"
#include "MySaveGame.h"

// Sets default values
APlayerPawn::APlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CurrentCharges = MaxCharges;
	reChargeTime = MaxChargeTime;
	TimeToBeam = MaxBeamTime;
	SpeedVect = FVector(0);
	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh0"));
	Beam = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Beam0"));
	MainTheme = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioLong"));
	if (MainTheme->IsValidLowLevelFast())
	{
		MainTheme->bAutoActivate = false;
	}
	FailSound = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioFail"));
	if (FailSound->IsValidLowLevelFast())
	{
		FailSound->bAutoActivate = false;
	}
	BeamSound = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioBeam"));
	if (BeamSound->IsValidLowLevelFast())
	{
		BeamSound->bAutoActivate = false;
	}
	MainCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("VFX0"));
	//ProjectileMesh->OnComponentBeginOverlap.AddDynamic(this, &AMyAsteroid::OnBeginOverlap);
	//ProjectileMesh->OnComponentHit.AddDynamic(this, &AMyAsteroid::OnHit);		// set up a notification for when this component hits something
	RootComponent = MainCollision;
	Body->SetupAttachment(RootComponent);
	Beam->SetupAttachment(Body);
	Beam->SetVisibility(false);
	BeamEnemies={ AUFOHard::StaticClass(),AMyAsteroid::StaticClass(),AUFOLight::StaticClass() };
	SweepHit = &TempHit;//Very important, ue4 pointers wouldnt work without right part
}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	Beam->Deactivate();
	Beam->SetVisibility(true);
	if (MainTheme != NULL)
	{
		MainTheme->Play();
		//MainTheme->OnAudioFinished.AddDynamic(this, &APlayerPawn::ReplaySound);
	}
}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (IsBeaming)
	{
		Beaming(DeltaTime);
	}
	else
	{
		SetActorRotation(FRotator(0, (MouseLoc - GetActorLocation()).Rotation().Yaw,0));
		if (DeltaSpeed.Size() > 0)
		{
			DeltaSpeed.GetClampedToMaxSize(1.f);
			SpeedVect = (SpeedVect + GetActorRotation().RotateVector(DeltaSpeed*Acceleration*DeltaTime)).GetClampedToMaxSize(MaxSpeed);
			FireShot();
		}
	}
	AddActorWorldOffset(SpeedVect*DeltaTime,true,SweepHit);
	//DebugHelper(SpeedVect * DeltaTime);
	if (SweepHit!=NULL) 
		 if (SweepHit->bBlockingHit)
	{
		SpeedVect=FVector::VectorPlaneProject(SpeedVect, SweepHit->Normal.GetSafeNormal2D());
		AddActorWorldOffset(SpeedVect*(1.f - SweepHit->Time)*DeltaTime,true,SweepHit);
	}
	if (MaxCharges != CurrentCharges)
	{
		reChargeTime -= DeltaTime;
		if (reChargeTime <= 0.f)
		{
			reChargeTime = MaxChargeTime;
			CurrentCharges++;
			PlayerCursor->Redraw(CurrentCharges);
		}
	}
}


float APlayerPawn::TakeDamage(float Damage, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	SetCanBeDamaged (false);
	Health--;
	if (Health > 0)
	{
		SetActorLocation(FVector(0.f, 0.f, 230.f));
		CurrentCharges = MaxCharges;
		if (PlayerCursor != NULL) PlayerCursor->Redraw(CurrentCharges);
		IsBeaming = false;
		Beam->Deactivate();
		reChargeTime = MaxChargeTime;
		Level->GetTimerManager().SetTimer(DeathHandle, this, &APlayerPawn::AfterDeath, 2.f, false);
		SpeedVect = FVector(0);
	}
	else
	{
		if (Controller != NULL) {
			Controller->PauseGame();
			Controller->HUD->EndGame();
		}
	}
	return Damage;
}

void APlayerPawn::AfterDeath()
{
	SetCanBeDamaged(true);
	for (TActorIterator<AUFOHard> ActorItr(Level); ActorItr; ++ActorItr)
	{
		ActorItr->ChaseEnemy(this);
	}

}

void APlayerPawn::AfterShoot()
{
	CanFire = true;
}

void APlayerPawn::ReplaySound()
{
	if (MainTheme!=NULL)	MainTheme->Play();
}

void APlayerPawn::FireShot()
{
	if (CanFire&&IsShooting)
	{
		Level->SpawnActor<APlayerProjectile>(ProjectileClass,GetActorLocation() + GetActorRotation().RotateVector(GunOffset), GetActorRotation());
		UGameplayStatics::PlaySoundAtLocation(Level, ShootSound, GetActorLocation() + GetActorRotation().RotateVector(GunOffset));
		CanFire = false;
		Level->GetTimerManager().SetTimer(ShootHandle, this, &APlayerPawn::AfterShoot,ShootRate, false);
	}

}


void APlayerPawn::Beaming(float Tick)
{
	TimeToBeam -= Tick;
	Beam->SetBeamTargetPoint(0, GetActorLocation() + GetActorForwardVector() * 4000.f, 0);
	if (TimeToBeam <= 0.f)
	{
		TArray<FHitResult> AllEnemies;
		FCollisionObjectQueryParams Objects(ECollisionChannel::ECC_WorldDynamic);
		Objects.AddObjectTypesToQuery(ECollisionChannel::ECC_Pawn);
		FHitResult SingleEnemy;
		Beam->Deactivate();
		Level->SweepMultiByObjectType(AllEnemies, GetActorLocation(), GetActorForwardVector()*4000.f + GetActorLocation(), FQuat(EForceInit::ForceInitToZero), Objects, FCollisionShape::MakeBox(FVector(14.f)));
		for (int32 i = 0; i < AllEnemies.Num(); i++)
		{
			if (BeamEnemies.Contains(AllEnemies[i].Actor->GetClass()))
			{
				AllEnemies[i].Actor->TakeDamage(-1.f, FDamageEvent(), GetInstigatorController(), this);
			}
		}
		TimeToBeam = MaxBeamTime;
		IsBeaming = false;
	}
}

int32 APlayerPawn::SaveGame()
{
	UMySaveGame* InterSave;
	FScoreLine NewLine;
	NewLine.Score = Score;
	NewLine.String = TEXT("");
	InterSave = Cast<UMySaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("HighScore"), 0));
	if (InterSave == NULL) InterSave = Cast<UMySaveGame>(UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass()));
	InterSave->MainTable.Add(NewLine);
	InterSave->MainTable.Sort();
	InterSave->MainTable.Reset(InterSave->MaxSize);
	UGameplayStatics::SaveGameToSlot(InterSave, TEXT("HighScore"), 0);
	return InterSave->MainTable.FindLast(NewLine);
	//return -1;

}

void APlayerPawn::StartBeaming()
{
	if (IsBeaming) return;
	if ( CurrentCharges < 1)
	{
		FailSound->Play();
		return;
	}
	CurrentCharges--;
	IsBeaming = true;
	PlayerCursor->Redraw(CurrentCharges);
	Beam->Activate(true);
	Beam->SetBeamTargetPoint(0, GetActorLocation() + GetActorForwardVector()*4000.f, 0);
	BeamSound->Play();
}



APlayerPawn::~APlayerPawn()
{
	//clearing timers in destructor isnt necessary, moreover next line isnt working at all,moreover this line isnt working only in destructor
	//GetWorldTimerManager().ClearAllTimersForObject(this);
}
