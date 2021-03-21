// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ScoreLine.generated.h"

/**
 * 
 */
USTRUCT()
struct ASTEROIDS_API FScoreLine
{
	GENERATED_BODY()
public:
		FScoreLine();
		int32 Score;
		FString String;
		friend bool operator<(const FScoreLine& First, const FScoreLine& Second);
		friend bool operator==(const FScoreLine& First, const FScoreLine& Second) { return First.Score == Second.Score&&First.String == Second.String; }
	
	
};
