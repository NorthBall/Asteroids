// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CursorWidget.generated.h"

class UImage;
/**
 * 
 */
UCLASS()
class ASTEROIDS_API UCursorWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UCursorWidget(const FObjectInitializer& ObjectInitializer);
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
		TArray<UImage*> Images;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
			FLinearColor Green;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
			FLinearColor Red;
	UFUNCTION()
		void Redraw(int32 Charges);
	
	
};
