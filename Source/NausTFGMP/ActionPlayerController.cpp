// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionPlayerController.h"

#include "ActionGameMode.h"
#include "PilotActionPawn.h"
#include "ArtilleryActionPawn.h"
#include "ActionPawn.h"
#include "GameFramework/GameModeBase.h"
#include "Net/UnrealNetwork.h"

AActionPlayerController::AActionPlayerController() {

	bReplicates = true;

	ConstructorHelpers::FClassFinder <APilotActionPawn> refPilotActionPawnBP(TEXT("/Game/Blueprints/Action/PilotActionPawn_BP"));
	pilotClass = refPilotActionPawnBP.Class;

	ConstructorHelpers::FClassFinder <AArtilleryActionPawn> refArtilleryActionPawnBP(TEXT("/Game/Blueprints/Action/ArtilleryActionPawn_BP"));
	artilleryClass = refArtilleryActionPawnBP.Class;

}


void AActionPlayerController::BeginPlay() {

	Super::BeginPlay();


	SetPilot();

}

UClass* AActionPlayerController::GetPlayerPawnClass()
{
	return myPawn;
}

void AActionPlayerController::ServerSetPlayerControllerPawn_Implementation(TSubclassOf<AActionPawn> MyPawnClass)
{

	myPawn = MyPawnClass;
	
	
	if (UWorld* World = GetWorld())
	{
		if (AActionGameMode* GameMode = Cast<AActionGameMode>(World->GetAuthGameMode()))
		{
			AActionPlayerController* controllerRef = this;

			//Muy importante destruir el Pawn assignado al PlayerController antes del beginPlay, ya que en caso contrario el restart no accionara GetDefaultPawnClassForController
			//sino que reusaarà el existente
			controllerRef->GetPawn()->Destroy();
			GameMode->RestartPlayer(controllerRef);
		}
	}
	
}


bool AActionPlayerController::ServerSetPlayerControllerPawn_Validate(TSubclassOf<AActionPawn> MyPawnClass)
{

	if(MyPawnClass)
	{

		return true;
	}

	return false;
}

void AActionPlayerController::SetPilot_Implementation()
{
	if(IsLocalController())
		ServerSetPlayerControllerPawn(pilotClass);
}


void AActionPlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AActionPlayerController, myPawn);
}

