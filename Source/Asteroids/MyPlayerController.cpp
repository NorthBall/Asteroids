// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "MyPlayerController.h"
#include "Camera/CameraActor.h"
#include "Engine/World.h"
#include "Camera/CameraComponent.h"
#include "PlayerPawn.h"
#include "EngineUtils.h"
#include "CursorWidget.h"
#include "MyHUD.h"
#include "Components/VerticalBox.h"
AMyPlayerController::AMyPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMyPlayerController::AxisX(float value)
{
	PlayerModel->DeltaSpeed.X = value;
}

void AMyPlayerController::AxisY(float value)
{
	PlayerModel->DeltaSpeed.Y = value;
}

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();
	Level = GetWorld();
	if(Level != NULL)
	{
		
		/*TActorIterator<ACameraActor> Iter(Level);
		if (Iter)
		{
			MainCamera = *Iter;
		}
		else
		{
			MainCamera = Level->SpawnActor<ACameraActor>(ACameraActor::StaticClass(), FVector(0.f, 0.f, 910.f), FRotator(-90.f, 0.f, -0.f));
		}
		MainCamera->GetCameraComponent()->SetProjectionMode(ECameraProjectionMode::Orthographic);
		MainCamera->GetCameraComponent()->SetOrthoWidth(4800.f);
		MainCamera->GetCameraComponent()->SetAspectRatio(16.f / 9.f);
		SetViewTarget(MainCamera);*/
		if (PlayerCursorClass)
		{
			PlayerCursor = CreateWidget<UCursorWidget>(this, PlayerCursorClass);
			SetMouseCursorWidget(EMouseCursor::Default, PlayerCursor);
		}
		if (HUDClass)
		{
			HUD = CreateWidget<UMyHUD>(this, HUDClass);
			HUD->AddToViewport();
		}
		PlayerModel = Cast<APlayerPawn>(GetPawn());
		if (PlayerModel != NULL&&HUD!=NULL&&PlayerCursor!=NULL)
		{
			PlayerModel->Level = Level;
			PlayerModel->Controller = this;
			PlayerModel->PlayerCursor = PlayerCursor;
			HUD->ModelRef = PlayerModel;
			PlayerCursor->Redraw(PlayerModel->GetCharges());
		}
		bShowMouseCursor = true;
	}

}
void AMyPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	GetHitResultUnderCursor(ECollisionChannel::ECC_WorldStatic, false, Hit);
	if (PlayerModel!=NULL)	PlayerModel->MouseLoc=Hit.Location;
}
void AMyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAction("LeftClick", IE_Pressed, this, &AMyPlayerController::StartShooting);
	InputComponent->BindAction("LeftClick", IE_Released, this, &AMyPlayerController::EndShooting);
	InputComponent->BindAction("Pause", IE_Pressed, this, &AMyPlayerController::PauseGame);
	InputComponent->BindAction("RightClick", IE_Pressed, this, &AMyPlayerController::StartBeaming);
	InputComponent->BindAxis("MoveRight", this, &AMyPlayerController::AxisY);
	InputComponent->BindAxis("MoveForward", this, &AMyPlayerController::AxisX);
}
void AMyPlayerController::StartShooting()
{
	PlayerModel->IsShooting = true;
}
void AMyPlayerController::StartBeaming()
{
	PlayerModel->StartBeaming();
}
void AMyPlayerController::EndShooting()
{
	PlayerModel->IsShooting = false;
}
void AMyPlayerController::PauseGame()
{
	SetPause(true);
	if (HUD != NULL) if (HUD->QuickMenu != NULL) HUD->QuickMenu->SetVisibility(ESlateVisibility::Visible);
	if (!CasualCursor->IsValidLowLevelFast() && CasualCursorClass)
	{
		CasualCursor = CreateWidget<UUserWidget>(this, CasualCursorClass);
	}
	SetMouseCursorWidget(EMouseCursor::Default, CasualCursor);
}
AMyPlayerController::~AMyPlayerController()
{
	if (MainCamera->IsValidLowLevel()) MainCamera->Destroy();
}
