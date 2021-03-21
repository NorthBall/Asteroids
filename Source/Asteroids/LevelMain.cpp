// Fill out your copyright notice in the Description page of Project Settings.

#include "LevelMain.h"
#include "Engine/World.h"
#include "PlayerPawn.h"
#include "EngineUtils.h"

ALevelMain::ALevelMain()
{
}

void ALevelMain::BeginPlay()
{
	
	if (TActorIterator<APlayerPawn>(GetWorld()))
	{
		MainPlayer = *TActorIterator<APlayerPawn>(GetWorld());
	}
	AfterBeginPlay();
	Super::BeginPlay();
}


