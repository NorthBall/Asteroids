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

ALevelMain::ALevelMain()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ALevelMain::BeginPlay()
{
	if (TActorIterator<APlayerPawn>(GetWorld()))
	{
		MainPlayer = *TActorIterator<APlayerPawn>(GetWorld());
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
	Super::Tick(DeltaTime);
	AsteroidCurrentTime += DeltaTime;
	if (AsteroidCurrentTime >= AsteroidSpawnTime)
	{
		SpawnEnemy(EEnemyTypes::Asteroid);
		AsteroidCurrentTime -= AsteroidSpawnTime;
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
	if (Level > 2)
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



void ALevelMain::SpawnEnemy(EEnemyTypes EnemyType)
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
		CurentAsteroid->Enemy = MainPlayer;
		CurentAsteroid->ProjectileMovement->Velocity = FRotator(0,  FMath::RandRange(float(0), float(360)),0 ).Vector() * FMath::RandRange(35, 100);
		CurentAsteroid->Health = FMath::RandRange(1, Level);
		break;
	case EEnemyTypes::UFOHard:
		CurentHard = GetWorld()->SpawnActor<AUFOHard>(HardUFOClass, FTransform(SpawnRotation, SpawnPoint, SpawnScale));
		CurentHard->Enemy = MainPlayer;
		break;
	case EEnemyTypes::UFOLight:
		CurentLight = GetWorld()->SpawnActor<AUFOLight>(LightUFOClass, FTransform(SpawnRotation, SpawnPoint, SpawnScale));
		CurentLight->Enemy = MainPlayer;
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