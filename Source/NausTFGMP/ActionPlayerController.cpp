// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionPlayerController.h"

#include "ActionGameMode.h"
#include "PilotActionPawn.h"
#include "ArtilleryActionPawn.h"
#include "ActionPawn.h"
#include "GameFramework/GameModeBase.h"
#include "Net/UnrealNetwork.h"
#include "Gui/Menu/MainMenu_EP.h"
#include "Gui/Menu/InGameMenu_EP.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"

AActionPlayerController::AActionPlayerController() {

	//El actor se replica para que se tenga en cuenta las modificaciones del servidor, por ejemplo el cambi� de defaultPawn
	bReplicates = true;

	//Busca el PilotActionBP y guarda la referencia de la clase
	InitializePilotPawnClass();

	ConstructorHelpers::FClassFinder <AArtilleryActionPawn> refArtilleryActionPawnBP(TEXT("/Game/Blueprints/Action/ArtilleryActionPawn_BP"));
	artilleryClass = refArtilleryActionPawnBP.Class;

	//Busca el mainMenuBP y guarda la referencia de la clase
	InitializeMainMenuClass();

	InitializeInGameMenuClass();

	isInGameMenuOpen = false;

}


void AActionPlayerController::BeginPlay() {

	Super::BeginPlay();

	//Por defecto el usuario usar� un pawn de tipo PilotAction, en caso de no haver pawn por defecto gameMode usara defaultPawn de GameMode
	SetPilot();

	CreaMainMenu();

	CreaInGameMenu();

	//Crea el widget de tipo mainMenu y lo muestra
	LoadMainMenu();

	//Binding signals
	BindSignals();

}

UClass* AActionPlayerController::GetPlayerPawnClass()
{
	return myPawnClass;
}


void AActionPlayerController::ServerSetPlayerControllerPawn_Implementation(TSubclassOf<AActionPawn> MyPawnClass)
{

	myPawnClass = MyPawnClass;
	
	if (UWorld* World = GetWorld())
	{
		//Podemos hacer get de GameMode ya que sabemos que esto se ejecutara en el servidor, igualmente usamos un condicional por prevencion
		if (AActionGameMode* GameMode = Cast<AActionGameMode>(World->GetAuthGameMode()))
		{
			AActionPlayerController* controllerRef = this;

			//Muy importante destruir el Pawn assignado al PlayerController antes del RestartPlayer, ya que en caso contrario el restart no llamara GetDefaultPawnClassForController
			//sino que reusar� el existente
			controllerRef->GetPawn()->Destroy();
			GameMode->RestartPlayer(controllerRef);

		}
	}
	
}


bool AActionPlayerController::ServerSetPlayerControllerPawn_Validate(TSubclassOf<AActionPawn> MyPawnClass)
{
	//Comprovar que el pawn enviado por el usuario no es nullptr, no es necessario mas comprovaciones ya que el parametro se ha reducido a AActionPawn
	if(MyPawnClass)
	{

		return true;
	}

	return false;
}

void AActionPlayerController::SetPilot_Implementation()
{
	//El cliente debe decidir que pawn quiere, de otra manera si usaramos otro metodo mas personalizado para elegir el pawn y el servidor tambi�n ejecuta esta instruccion todos tendrian el mismo pawn definido por el servidor
	if (IsLocalController())
	{
		ServerSetPlayerControllerPawn(pilotClass);

		if(isInGameMenuOpen)
		{

			UnloadInGameMenu();
		}

	}

}

void AActionPlayerController::SetArtillery_Implementation()
{
	//El cliente debe decidir que pawn quiere, de otra manera si usaramos otro metodo mas personalizado para elegir el pawn y el servidor tambi�n ejecuta esta instruccion todos tendrian el mismo pawn definido por el servidor
	if (IsLocalController())
	{
		ServerSetPlayerControllerPawn(artilleryClass);

		if (isInGameMenuOpen)
		{

			UnloadInGameMenu();
		}
	}

}


//parametro 0 hace pawn de playerController ser pilot, cualquier otro lo transforma en artillery
void AActionPlayerController::SetPlayerControllerPawn(int index)
{

	//No es necessario comprovar quien ejecuta esta funci�n ya que en SetArtillery y setPawn ya se mira que sea en local

	if(index)
	{
		SetArtillery();
	}else
	{

		SetPilot();
	}
}

void AActionPlayerController::InitializeMainMenuClass()
{
	ConstructorHelpers::FClassFinder <UMainMenu_EP> mainMenuClassBP(TEXT("/Game/Gui/Menu/MainMenu_BP"));
	mainMenuClass = mainMenuClassBP.Class;
	
}

void AActionPlayerController::InitializeInGameMenuClass()
{

	ConstructorHelpers::FClassFinder <UInGameMenu_EP> inGameMenuClassBP(TEXT("/Game/Gui/Menu/InGameMenu_BP"));
	inGameMenuClass = inGameMenuClassBP.Class;
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


	if (IsLocalPlayerController())
	{

		mainMenu->bIsFocusable = true;
		mainMenu->AddToViewport();
		ShowNotLockingMouseCursor(mainMenu);
	}
}

void AActionPlayerController::UnloadMainMenu()
{

	//Unicamente queremos que la HUD la tengan los clientes y alimentarla con datos del servidor, en el caso de un solo jugador 
	//si serà la autoridad por lo tanto si està controlado localmente también mostramos el menu
	if (IsLocalPlayerController())
	{

		mainMenu->RemoveFromViewport();

		HideAndLockMouseCursor(mainMenu);
		mainMenu->bIsFocusable = false;
		
	}
}

void AActionPlayerController::LoadInGameMenu()
{

	if (IsLocalPlayerController())
	{
		isInGameMenuOpen = true;
		inGameMenu->bIsFocusable = true;
		inGameMenu->AddToViewport();
		ShowNotLockingMouseCursor(inGameMenu);
	}
}

void AActionPlayerController::UnloadInGameMenu()
{

	if (IsLocalPlayerController())
	{

		isInGameMenuOpen = false;
		inGameMenu->RemoveFromViewport();

		HideAndLockMouseCursor(inGameMenu);
		inGameMenu->bIsFocusable = false;

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

void AActionPlayerController::BindSignals()
{

	//El servidor no puede crear widget ya que no tiene pantalla, por lo tanto si accedemos a un widget siendo el servidor crashea
	if(IsLocalPlayerController())
	{

		mainMenu->signalOnClickExit.AddDynamic(this, &AActionPlayerController::ExitGame); 
		mainMenu->signalOnClickPlay.AddDynamic(this, &AActionPlayerController::UnloadMainMenu);

		inGameMenu->signalOnClickExit.AddDynamic(this, &AActionPlayerController::ExitGame);
		inGameMenu->signalOnClickUsePilotAsPlayerControllerPawn.AddDynamic(this, &AActionPlayerController::SetPilot);
		inGameMenu->signalOnClickUseArtilleryAsPlayerControllerPawn.AddDynamic(this, &AActionPlayerController::SetArtillery);
		inGameMenu->signalOnClickBack.AddDynamic(this, &AActionPlayerController::UnloadInGameMenu);

	}
}

void AActionPlayerController::CreaMainMenu()
{

	if (IsLocalPlayerController())
	{
		mainMenu = CreateWidget<UMainMenu_EP>(this, mainMenuClass);

	}
}

void AActionPlayerController::CreaInGameMenu()
{

	if (IsLocalPlayerController())
	{
		inGameMenu = CreateWidget<UInGameMenu_EP>(this, inGameMenuClass);

	}
}

void AActionPlayerController::ExitGame()
{
	
	UKismetSystemLibrary::QuitGame(GetWorld(), this, EQuitPreference::Quit, false);

}

void AActionPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if(IsLocalPlayerController())
		InputComponent->BindAction("OpenInGameMenu", EInputEvent::IE_Pressed, this, &AActionPlayerController::LoadInGameMenu);
}


void AActionPlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AActionPlayerController, myPawnClass);
}

