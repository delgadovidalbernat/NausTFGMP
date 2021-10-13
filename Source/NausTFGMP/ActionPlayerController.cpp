// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionPlayerController.h"
#include "PilotActionPawn.h"
#include "Gui/Menu/MainMenu_EP.h"

AActionPlayerController::AActionPlayerController() {

	InitializePilotPawnClass();

	InitializeMainMenuClass();

	
}


void AActionPlayerController::BeginPlay() {

	Super::BeginPlay();


	pilot = GetWorld()->SpawnActor<APilotActionPawn>(pilotClass);
	Possess(pilot);

	LoadMainMenu();
}

void AActionPlayerController::InitializeMainMenuClass()
{
	ConstructorHelpers::FClassFinder <UMainMenu_EP> mainMenuClassBP(TEXT("/Game/Gui/Menu/MainMenu_BP"));
	mainMenuClass = mainMenuClassBP.Class;
}

void AActionPlayerController::InitializePilotPawnClass()
{

	ConstructorHelpers::FClassFinder <APilotActionPawn> pilotClassBP(TEXT("/Game/Blueprints/Action/PilotActionPawn_BP"));
	pilotClass = pilotClassBP.Class;
}

void AActionPlayerController::LoadMainMenu()
{

	//Unicamente queremos que la HUD la tengan los clientes y alimentarla con datos del servidor, en el caso de un solo jugador 
	//si serà la autoridad por lo tanto si està controlado localmente también mostramos el menu
	if (pilot->IsLocallyControlled() || !HasAuthority())
	{

		mainMenu = CreateWidget<UMainMenu_EP>(this, mainMenuClass);
		mainMenu->AddToViewport();
		ShowNotLockingMouseCursor(mainMenu);
	}
}

void AActionPlayerController::ShowNotLockingMouseCursor(UUserWidget* UIMenu)
{

	FInputModeUIOnly InputModeData;
	InputModeData.SetWidgetToFocus(UIMenu->TakeWidget());
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

	SetInputMode(InputModeData);
	bShowMouseCursor = true;
}
