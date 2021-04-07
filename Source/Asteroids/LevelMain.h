// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "Camera/CameraActor.h"
#include "Curves/CurveVector.h"
#include "UFOTypes.h"
#include "Runtime/Engine/Classes/Engine/DataTable.h"
#include "LevelMain.generated.h"

class APlayerPawn;
/**
 * 
 */

UCLASS()
class ASTEROIDS_API ALevelMain : public ALevelScriptActor
{
	GENERATED_BODY()
public:
	ALevelMain();
	virtual void BeginPlay() override;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Support")
		APlayerPawn* MainPlayer;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Support")
		ACameraActor* TopDownCamera;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Support")
		UCurveVector* SpawnLines;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category ="Support")
		TSubclassOf<class AMyAsteroid> AsteroidClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Support")
		TSubclassOf<class AUFOHard> HardUFOClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Support")
		TSubclassOf<class AUFOLight> LightUFOClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Support")
		UDataTable* LevelUpdateTable;
	UFUNCTION(BlueprintImplementableEvent)
		void AfterBeginPlay();


	virtual void Tick(float DeltaTime) override;
	void SpawnEnemy(EEnemyTypes EnemyType);
	void LevelUp();
	/* support variables*/
	float AsteroidCurrentTime=0;
	float AsteroidSpawnTime = 1.0;
	float HardUFOCurrentTime = 0;
	float HardUFOSpawnTime = 1.2;
	float LightUFOCurrentTime = 0;
	float LightUFOSpawnTime = 2.0;
	float LevelCurrentTime = 0;
	float LevelUpdateTime;
	int32 Level = 1;
	//utility variables

	
};
