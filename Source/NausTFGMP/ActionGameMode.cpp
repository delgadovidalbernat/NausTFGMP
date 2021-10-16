// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionGameMode.h"
#include "ActionGameState.h"
#include "ActionPlayerController.h"
#include "ActionPlayerState.h"
#include "PilotActionPawn.h"
#include "ActionPawn.h"

AActionGameMode::AActionGameMode() {

	InitializeDefaultPawnClass();

	//Este valor es null ya que asi el moto va a usar el return de GetDefaultPawnClassForController_Implementation
	//DefaultPawnClass = nullptr;

	GameStateClass = AActionGameState::StaticClass();
	PlayerControllerClass = AActionPlayerController::StaticClass();
	PlayerStateClass = AActionPlayerState::StaticClass();

}

void AActionGameMode::InitializeDefaultPawnClass()
{

	ConstructorHelpers::FClassFinder <APilotActionPawn> refBlueprint(TEXT("/Game/Blueprints/Action/PilotActionPawn_BP"));
	pilotClass = refBlueprint.Class;
}

UClass* AActionGameMode::GetDefaultPawnClassForController_Implementation(AController* InController)
{

	AActionPlayerController* MyController = Cast<AActionPlayerController>(InController);

	if(MyController)
	{

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
