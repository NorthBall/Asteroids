// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Styling/SlateColor.h"
#include "MyHUD.generated.h"

class APlayerPawn;
class UMainMenuC;
class UCanvasPanel;
class UButton;
class UTextBlock;
/**
 * 
 */
UCLASS()
class ASTEROIDS_API UMyHUD : public UUserWidget
{
	GENERATED_BODY()
public:
	UMyHUD(const FObjectInitializer& Obj);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Reference")
		APlayerPawn* ModelRef;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Reference")
		UMainMenuC* MenuRef;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variables")
		int32 SavedScore=0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variables")
		int32 HSLineNumber;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
		TSubclassOf<class UMainMenuC> MenuClass;
	UFUNCTION()
		void EndGame();
	//buttons
	UFUNCTION(BlueprintCallable)
		void Resume();
	UFUNCTION(BlueprintCallable)
		FText ChangeHealth();
	UFUNCTION(BlueprintCallable)
		void ToMainMenu();
	UFUNCTION(BlueprintCallable)
		void Quit();
	UFUNCTION(BlueprintCallable)
		FText YourScore();
	UFUNCTION(BlueprintCallable)
		FText HighScore();
	UCanvasPanel* QuickMenu;
	//buttons ref
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Buttons")
		UButton* ResumeB;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Buttons")
		UTextBlock* Health;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Buttons")
		UTextBlock* EndGameW;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Colors")
		TArray<FSlateColor> ColorsHealth;
};
