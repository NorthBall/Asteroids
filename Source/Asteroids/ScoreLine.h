// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ScoreLine.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct ASTEROIDS_API FScoreLine
{
	GENERATED_BODY()
public:
		FScoreLine();
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Score;
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString String;
		friend bool operator<(const FScoreLine& First, const FScoreLine& Second);
		friend bool operator==(const FScoreLine& First, const FScoreLine& Second) { return First.Score == Second.Score&&First.String == Second.String; }
	
	
};
