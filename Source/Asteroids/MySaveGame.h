// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "ScoreLine.h"
#include "MySaveGame.generated.h"
//class FScoreLine;
/**
 * 
 */
UCLASS()
class ASTEROIDS_API UMySaveGame : public USaveGame
{
	GENERATED_BODY()
public:
		TArray<FScoreLine> MainTable;
		int32 MaxSize=20;
	
};
