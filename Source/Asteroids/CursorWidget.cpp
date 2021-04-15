// Fill out your copyright notice in the Description page of Project Settings.

#include "CursorWidget.h"
#include "PlayerPawn.h"
#include "Components/Image.h"

UCursorWidget::UCursorWidget(const FObjectInitializer& ObjectInitializer):UUserWidget(ObjectInitializer)
{
	for (int32 i = 0; i < Images.Num(); i++)
	{
		//Images.Add(CreateDefaultSubobject<UImage>(FName(TEXT("Image"), i)));
		Images[i]->SetColorAndOpacity(Green);
	}
}

void UCursorWidget::Redraw(int32 Charges)
{
	for (i = 0; i < Charges; i++) Images[i]->SetColorAndOpacity(Green);
	for (i = i; i < 3; i++) Images[i]->SetColorAndOpacity(Red);
}
