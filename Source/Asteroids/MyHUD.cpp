// Fill out your copyright notice in the Description page of Project Settings.

#include "MyHUD.h"
#include "Kismet/GameplayStatics.h"
#include "MySaveGame.h"	
#include "Components/VerticalBox.h"
#include "MyPlayerController.h"
#include "PlayerPawn.h"
#include "Components/Button.h"
#include "CursorWidget.h"
#include "MainMenuC.h"
#include "Components/TextBlock.h"
#include "Engine/World.h"
#include "Kismet/KismetSystemLibrary.h"

void UMyHUD::EndGame()
{
	EndGameW->SetVisibility(ESlateVisibility::Visible);
	ResumeB->SetIsEnabled(false);
}
void UMyHUD::Resume()
{
	AMyPlayerController* InterPC;
	QuickMenu->SetVisibility(ESlateVisibility::Hidden);
	InterPC = Cast<AMyPlayerController>(ModelRef->GetController());
	if (InterPC != NULL)
	{
		InterPC->SetPause(false);
		InterPC->SetMouseCursorWidget(EMouseCursor::Default, InterPC->PlayerCursor);
	}
}
FText UMyHUD::ChangeHealth()
{
	if (ModelRef == NULL) 	return FText().FromString(TEXT("Menu"));
	static FString InterS;
	InterS = TEXT("Health: ");
	InterS.AppendInt(ModelRef->Health);
	if (ColorsHealth.IsValidIndex(ModelRef->Health)) Health->SetColorAndOpacity(ColorsHealth[ModelRef->Health]);
	return FText().FromString(InterS); //FString(TEXT("Health: ")).AppendInt(ModelRef->Health));
	//return FText();
}
void UMyHUD::ToMainMenu()
{
	HSLineNumber=ModelRef->SaveGame();
	ResumeB->SetIsEnabled(true);
	RemoveFromParent();
	if (!MenuRef->IsValidLowLevel()) MenuRef = CreateWidget<UMainMenuC>(this, MenuClass);
	MenuRef->AddToViewport();
	MenuRef->HSLineNumber = HSLineNumber;
	MenuRef->Reload();
	MenuRef->ShowHighscore();
}
void UMyHUD::Quit()
{
	APlayerController* Controller;
	Controller = ModelRef->GetController<APlayerController>();
	if (Controller != NULL)
	{
		Controller->ConsoleCommand(FString("quit"));
	}
	/*bool newvar;
	TCHAR* a(L"Navigation");
	if (GetWorld() != NULL) {
		newvar = GetWorld()->Exec(GetWorld(), a, *GLog);
		if (newvar) UE_LOG(LogTemp, Warning, TEXT("Successfully executed"));
		//UKismetSystemLibrary::ExecuteConsoleCommand(GetWorld(), FString("quit"));
	}*/
	
}

FText UMyHUD::YourScore()
{
	if (ModelRef)return FText().FromString(FString(TEXT("Score: ")) + FString().FromInt(ModelRef->Score));
	else return FText().FromString(FString("Menu"));
}
FText UMyHUD::HighScore()
{
	if(ModelRef)return FText().FromString(FString(TEXT("Highscore: ")) + FString().FromInt(SavedScore));
	else return FText().FromString(FString("Menu"));
}
UMyHUD::UMyHUD(const FObjectInitializer& Obj):UUserWidget(Obj)
{
	UMySaveGame* InterSave;
	InterSave=Cast<UMySaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("HighScore"), 0));
	if (InterSave != NULL) if (InterSave->MainTable.Num() > 0) SavedScore = InterSave->MainTable[0].Score;
}