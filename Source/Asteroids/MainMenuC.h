// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuC.generated.h"

class UScrollBox;
/**
 * 
 */
UCLASS()
class ASTEROIDS_API UMainMenuC : public UUserWidget
{
	GENERATED_BODY()
public:
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variables")
		int32 HSLineNumber;
		UFUNCTION(BlueprintCallable)
			void Reload();
		UFUNCTION(BlueprintCallable)
			void ShowHighscore();
		UFUNCTION(BlueprintCallable)
			void SaveComments();
		UFUNCTION(BlueprintCallable)
			void DeleteAllScores();
		UFUNCTION(BlueprintCallable)
			void Quit();
		UFUNCTION(BlueprintCallable)
			void StartNewGame();
		UFUNCTION(BlueprintCallable)
			void Options();
		void HideHighscore();

		int32 MaxLines;

		//buttons
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Buttons")
			UScrollBox* ScoreTable;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
			TSubclassOf<class UWidgetScoreLine> ScoreLineClass;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Buttons")
			class UCanvasPanel* ScoreMenu;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Buttons")
			class UVerticalBox* MainBox;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations")
			class UWidgetAnimation* NotImplemeted;
};
