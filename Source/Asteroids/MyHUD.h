// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Styling/SlateColor.h"
#include "MyHUD.generated.h"

class APlayerPawn;
class UMainMenuC;
class UVerticalBox;
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
	//init values
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Init")
		UButton* ResumeB;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Init")
		UTextBlock* EndGameW;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Init")
		TSubclassOf<class UMainMenuC> MenuClass;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Init")
		UTextBlock* Health;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Init")
		UVerticalBox* QuickMenu;
	UFUNCTION()
		void EndGame();
	//buttons
	UFUNCTION(BlueprintCallable)
		void Resume();
	UFUNCTION(BlueprintCallable,BlueprintPure)
		FText ChangeHealth();
	UFUNCTION(BlueprintCallable)
		void ToMainMenu();
	UFUNCTION(BlueprintCallable)
		void Quit();
	UFUNCTION(BlueprintCallable,BlueprintPure)
		FText YourScore();
	UFUNCTION(BlueprintCallable,BlueprintPure)
		FText HighScore();
	
	//buttons ref
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Reference")
		APlayerPawn* ModelRef;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Reference")
		UMainMenuC* MenuRef;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variables")
		int32 SavedScore = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variables")
		int32 HSLineNumber;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Colors")
		TArray<FSlateColor> ColorsHealth;
};
