// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionPlayerController.h"
#include "PilotActionPawn.h"
#include "Gui/Menu/MainMenu_EP.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"

AActionPlayerController::AActionPlayerController() {

	//Busca el PilotActionBP y guarda la referencia de la clase
	InitializePilotPawnClass();

	//Busca el mainMenuBP y guarda la referencia de la clase
	InitializeMainMenuClass();

	
}


void AActionPlayerController::BeginPlay() {

	Super::BeginPlay();


	pilot = GetWorld()->SpawnActor<APilotActionPawn>(pilotClass);
	Possess(pilot);

	//Crea el widget de tipo mainMenu y lo muestra
	LoadMainMenu();

	//Binding signals
	mainMenu->signalOnClickExit.AddDynamic(this, &AActionPlayerController::ExitGame);
	mainMenu->signalOnClickPlay.AddDynamic(this, &AActionPlayerController::UnloadMainMenu);
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
		mainMenu->bIsFocusable = true;
		mainMenu->AddToViewport();
		ShowNotLockingMouseCursor(mainMenu);
	}
}

void AActionPlayerController::UnloadMainMenu()
{

	//Unicamente queremos que la HUD la tengan los clientes y alimentarla con datos del servidor, en el caso de un solo jugador 
	//si serà la autoridad por lo tanto si està controlado localmente también mostramos el menu
	if (pilot->IsLocallyControlled() || !HasAuthority())
	{

		mainMenu->RemoveFromViewport();

		HideAndLockMouseCursor(mainMenu);
		mainMenu->bIsFocusable = false;
		
	}
}

void AActionPlayerController::ShowNotLockingMouseCursor(UUserWidget* UIMenu)
{

	FInputModeUIOnly InputModeData;
	InputModeData.SetWidgetToFocus(UIMenu->TakeWidget());
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

	SetInputMode(InputModeData);
	SetShowMouseCursor(true);
}

void AActionPlayerController::HideAndLockMouseCursor(UUserWidget* UIMenu)
{

	FInputModeGameOnly InputModeData;

	//UGameplayStatics::SetViewportMouseCaptureMode(GetWorld(), EMouseCaptureMode::NoCapture);

	SetShowMouseCursor(false);
	SetInputMode(InputModeData);
}

void AActionPlayerController::ExitGame()
{
	
	UKismetSystemLibrary::QuitGame(GetWorld(), this, EQuitPreference::Quit, false);

}
