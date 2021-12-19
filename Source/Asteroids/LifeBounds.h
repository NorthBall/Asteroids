// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "LifeBounds.generated.h"

/**
 * 
 */
UCLASS()
class ASTEROIDS_API ALifeBounds : public ATriggerBox
{
	GENERATED_BODY()
	virtual void BeginPlay() override;
	UFUNCTION()
		void OnEndOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
