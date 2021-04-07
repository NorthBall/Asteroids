// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UFOTypes.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EEnemyTypes :uint8 {
	Asteroid,
	UFOHard,
	UFOLight
};