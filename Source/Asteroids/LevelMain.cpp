// Fill out your copyright notice in the Description page of Project Settings.

#include "LevelMain.h"
#include "Engine/World.h"
#include "PlayerPawn.h"
#include "MyPlayerController.h"
#include "MyAsteroid.h"
#include "EngineUtils.h"
#include "UFOHard.h"
#include "UFOLight.h"
#include "Math/UnrealMathUtility.h"
#include "LevelTableRow.h"
#include "Components/SphereComponent.h"

ALevelMain::ALevelMain()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ALevelMain::BeginPlay()
{
	if (TActorIterator<APlayerPawn>(GetWorld()))
	{
		MainPlayer = *TActorIterator<APlayerPawn>(GetWorld());
		MainPlayer->BeamEnemies.Add(AsteroidClass);
		MainPlayer->BeamEnemies.Add(HardUFOClass);
		MainPlayer->BeamEnemies.Add(LightUFOClass);
	}
	AMyPlayerController* PlContr = GetWorld()->GetFirstPlayerController<AMyPlayerController>();
	if (PlContr != NULL)
	{
		PlContr->SetViewTargetWithBlend(TopDownCamera);
	}
	if (LevelUpdateTable != NULL) {
		FLevelTableRow* RowForLevel;
		RowForLevel = LevelUpdateTable->FindRow<FLevelTableRow>(FName(FString::FromInt(Level)), FString());
		LevelUpdateTime = RowForLevel->LevelTime;
		UE_LOG(LogTemp, Warning, TEXT("%f LevelTime"), LevelUpdateTime);
	}
		
	AfterBeginPlay();
	Super::BeginPlay();
}

void ALevelMain::Tick(float DeltaTime)
{
	static int tickRand;
	Super::Tick(DeltaTime);
	AsteroidCurrentTime += DeltaTime;
	if (AsteroidCurrentTime >= AsteroidSpawnTime)
	{
		tickRand = FMath::RandRange(1, Level);
		SpawnEnemy(EEnemyTypes::Asteroid,tickRand);
		AsteroidCurrentTime -= AsteroidSpawnTime/pow(2,Level-tickRand);
	}
	if (Level > 1)
	{
		HardUFOCurrentTime += DeltaTime;
		if (HardUFOCurrentTime >= HardUFOSpawnTime)
		{
			SpawnEnemy(EEnemyTypes::UFOHard);
			HardUFOCurrentTime -= HardUFOSpawnTime;
		}
	}
	if (Level > 0)
	{
		LightUFOCurrentTime += DeltaTime;
		if (LightUFOCurrentTime >= LightUFOSpawnTime)
		{
			SpawnEnemy(EEnemyTypes::UFOLight);
			LightUFOCurrentTime -= LightUFOSpawnTime;
		}
	}
	LevelCurrentTime += DeltaTime;
	if (LevelCurrentTime >= LevelUpdateTime)
	{
		LevelCurrentTime -= LevelUpdateTime;
		LevelUp();
	}
}



void ALevelMain::SpawnEnemy(EEnemyTypes EnemyType, int difficulty)
{
	static FVector SpawnPoint;
	static FRotator SpawnRotation;
	static FVector SpawnScale(0.6, 0.6, 0.6);
	static AMyAsteroid* CurentAsteroid;
	static AUFOHard* CurentHard;
	static AUFOLight* CurentLight;
	SpawnPoint = SpawnLines->GetVectorValue(FMath::RandRange(float(0), float(11.6)));
	SpawnRotation = FRotator(0, FMath::RandRange(float(0), float(360)), 0);
	switch (EnemyType)
	{
	case EEnemyTypes::Asteroid:
		CurentAsteroid = GetWorld()->SpawnActor<AMyAsteroid>(AsteroidClass, FTransform(SpawnRotation, SpawnPoint, SpawnScale));
		if (CurentAsteroid != NULL)
		{
			CurentAsteroid->Enemy = MainPlayer;
			//CurentAsteroid->MainCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel1,ECollisionResponse::ECR_Overlap);
			CurentAsteroid->ProjectileMovement->Velocity = FRotator(0, FMath::RandRange(-30,30), 0).RotateVector((Center-CurentAsteroid->GetActorLocation()).GetSafeNormal2D()) * FMath::RandRange(50, 150)*pow(speedMultiplier,Level-difficulty);
			CurentAsteroid->Health = difficulty;
			if (CurentAsteroid->Health > 1)
			{
				//CurentAsteroid->AddActorWorldOffset(FVector(0, 0, 200));
				CurentAsteroid->SetActorScale3D(SpawnScale *pow(1.4, CurentAsteroid->Health - 1));
			}
		}
		break;
	case EEnemyTypes::UFOHard:
		CurentHard = GetWorld()->SpawnActor<AUFOHard>(HardUFOClass, FTransform(SpawnRotation, SpawnPoint, SpawnScale));
		CurentHard->ChaseEnemy(MainPlayer);
		break;
	case EEnemyTypes::UFOLight:
		CurentLight = GetWorld()->SpawnActor<AUFOLight>(LightUFOClass, FTransform(SpawnRotation, SpawnPoint, SpawnScale));
		CurentLight->Init(MainPlayer);
		break;
	}
}
void ALevelMain::LevelUp()
{
	FLevelTableRow* RowForLevel;
	Level++;
	RowForLevel = LevelUpdateTable->FindRow<FLevelTableRow>(FName(FString::FromInt(Level)), FString());
	if (RowForLevel != NULL) {
		LevelUpdateTime = RowForLevel->LevelTime;
		AsteroidSpawnTime = RowForLevel->AsteroidTime;
		LightUFOSpawnTime = RowForLevel->LightUFOTime;
		HardUFOSpawnTime = RowForLevel->HardUFOTime;
	}
	
}