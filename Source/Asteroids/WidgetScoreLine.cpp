// Fill out your copyright notice in the Description page of Project Settings.

#include "WidgetScoreLine.h"
#include "Components/EditableTextBox.h"
#include "Components/EditableText.h"

void UWidgetScoreLine::WriteText(int32 PlaceI, int32 ScoreI, FString CommentS)
{
	Place->SetText(FText::AsNumber(PlaceI));
	Score->SetText(FText::AsNumber(ScoreI));
	Comment->SetText(FText::FromString(CommentS));
}
