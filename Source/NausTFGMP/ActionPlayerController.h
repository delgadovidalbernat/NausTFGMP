// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ActionPlayerController.generated.h"

class APilotActionPawn;
class UMainMenu_EP;

/**
 * 
 */
UCLASS()
class NAUSTFGMP_API AActionPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	AActionPlayerController();

	virtual void BeginPlay() override;

	void InitializeMainMenuClass();

	void InitializePilotPawnClass();

	void LoadMainMenu();

	UFUNCTION()
	void UnloadMainMenu();

	void ShowNotLockingMouseCursor(UUserWidget* UIMenu);

	void HideAndLockMouseCursor(UUserWidget* UIMenu);

	UFUNCTION()
	void ExitGame();


private:

	TSubclassOf<APilotActionPawn> pilotClass;
	APilotActionPawn* pilot;
	
	TSubclassOf<UMainMenu_EP> mainMenuClass;
	UMainMenu_EP* mainMenu;
};
