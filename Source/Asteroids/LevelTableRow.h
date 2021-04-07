// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/Engine/Classes/Engine/DataTable.h"
#include "LevelTableRow.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct ASTEROIDS_API FLevelTableRow : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float LevelTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float AsteroidTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float HardUFOTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float LightUFOTime;
};
