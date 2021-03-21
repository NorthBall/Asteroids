// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WidgetScoreLine.generated.h"

/**
 * 
 */
UCLASS()
class ASTEROIDS_API UWidgetScoreLine : public UUserWidget
{
	GENERATED_BODY()
public:
		void WriteText(int32 PlaceI, int32 ScoreI, FString CommentS);
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UEditableText* Score;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UEditableText* Place;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UEditableTextBox* Comment;

	
	
	
};
