// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionGameMode.h"
#include "ActionGameState.h"
#include "ActionPlayerController.h"
#include "ActionPlayerState.h"
#include "PilotActionPawn.h"
#include "ActionPawn.h"

AActionGameMode::AActionGameMode() {

	//Clase por defecto de GameState
	GameStateClass = AActionGameState::StaticClass();
	//Clase por defecto de PlayerController
	PlayerControllerClass = AActionPlayerController::StaticClass();
	//Clase por defecto de PlayerState
	PlayerStateClass = AActionPlayerState::StaticClass();

}


UClass* AActionGameMode::GetDefaultPawnClassForController_Implementation(AController* InController)
{

	AActionPlayerController* MyController = Cast<AActionPlayerController>(InController);

	if(MyController)
	{
		//Funcion en PlayerController que retorna el pawn escogido por el usuario
		UClass* defaultPawnClass = MyController->GetPlayerPawnClass();

		if(defaultPawnClass)
		{
			
			return defaultPawnClass;
		}

	}

	//En caso que defaultPawnClass sea null retun el defaultPawn de GameMode
	return Super::GetDefaultPawnClassForController_Implementation(InController);
}

void AActionGameMode::RestartPlayer(AController* NewPlayer)
{
	
	Super::RestartPlayer(NewPlayer);
	
}
