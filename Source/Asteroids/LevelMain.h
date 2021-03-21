// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
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
	UFUNCTION(BlueprintImplementableEvent)
		void AfterBeginPlay();
	
};
