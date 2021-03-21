// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

class ACameraActor;
class UWorld;
class APlayerPawn;
class UMyHUD;
class UUserWidget;
class UCursorWidget;
/**
 * 
 */
UCLASS()
class ASTEROIDS_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
		AMyPlayerController();
		~AMyPlayerController();
		UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Camera")
		ACameraActor* MainCamera;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
			UCursorWidget* PlayerCursor;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
			TSubclassOf<class UCursorWidget> PlayerCursorClass;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
			UUserWidget* CasualCursor;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
			TSubclassOf<class UUserWidget> CasualCursorClass;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
		UMyHUD* HUD;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
			TSubclassOf<class UMyHUD> HUDClass;
		UWorld* Level;
		APlayerPawn* PlayerModel;
		FHitResult Hit;
		UFUNCTION()
			void AxisX(float value);
		UFUNCTION()
			void AxisY(float value);
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void SetupInputComponent() override;
	void StartShooting();
	void StartBeaming();
	void EndShooting();
	void PauseGame();
};
