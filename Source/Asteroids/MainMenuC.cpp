// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenuC.h"
#include "MySaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "WidgetScoreLine.h"
#include "Components/ScrollBox.h"
#include "Components/EditableTextBox.h"
#include "Components/CanvasPanel.h"
#include "Components/VerticalBox.h"
#include "Animation/WidgetAnimation.h"

void UMainMenuC::Reload()
{
	UMySaveGame* InterSave;
	HideHighscore();
	InterSave = Cast<UMySaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("HighScore"), 0));
	//InterSave = Cast<UMySaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("HighScore"), 0));
	if (InterSave == NULL) return;
	ScoreTable->ClearChildren();
	UWidgetScoreLine* ChildWidget;
	MaxLines = InterSave->MaxSize;
	int32 i = 0;
	for (auto& ScoreLine : InterSave->MainTable)
	{
		ChildWidget=CreateWidget<UWidgetScoreLine>(this, ScoreLineClass);
		ScoreTable->AddChild(ChildWidget);
		ChildWidget->WriteText(++i, ScoreLine.Score, ScoreLine.String);
		if (HSLineNumber == i - 1)
		{
			ChildWidget->Comment->SetKeyboardFocus();
		}
	}
}

void UMainMenuC::ShowHighscore()
{
	ScoreMenu->SetVisibility(ESlateVisibility::Visible);
	MainBox->SetVisibility(ESlateVisibility::Hidden);
}

void UMainMenuC::SaveComments()
{
	UMySaveGame* InterSave;
	UWidgetScoreLine* InterWidget;
	InterSave = Cast<UMySaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("HighScore"), 0));
	if (InterSave == NULL) return;
	for (int32 i = 0; i < ScoreTable->GetChildrenCount(); i++)
	{
		InterWidget = Cast<UWidgetScoreLine>(ScoreTable->GetChildAt(i));
		if (InterWidget == NULL) continue;
		InterSave->MainTable[i].String = InterWidget->Comment->GetText().ToString();
	}
	UGameplayStatics::SaveGameToSlot(InterSave, TEXT("HighScore"), 0);
	HideHighscore();
}

void UMainMenuC::DeleteAllScores()
{
	UGameplayStatics::SaveGameToSlot(UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass()), TEXT("HighScore"), 0);
	HideHighscore();
}

void UMainMenuC::Quit()
{
	UWorld* InterW=GetWorld();
	if (InterW != NULL)
	{
		InterW->GetFirstPlayerController()->ConsoleCommand(FString("quit"));
		//GEngine->Exec(InterW, TEXT("quit"));
	}
}

void UMainMenuC::StartNewGame()
{
	UGameplayStatics::OpenLevel(GetWorld(), FName(TEXT("TwinStickExampleMap")));
}

void UMainMenuC::Options()
{
	PlayAnimation(NotImplemeted);
}

void UMainMenuC::HideHighscore()
{
	ScoreMenu->SetVisibility(ESlateVisibility::Hidden);
	MainBox->SetVisibility(ESlateVisibility::Visible);
}
