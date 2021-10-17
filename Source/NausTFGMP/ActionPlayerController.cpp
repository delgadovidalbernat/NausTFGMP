// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionPlayerController.h"

#include "ActionGameMode.h"
#include "PilotActionPawn.h"
#include "ArtilleryActionPawn.h"
#include "ActionPawn.h"
#include "GameFramework/GameModeBase.h"
#include "Net/UnrealNetwork.h"

AActionPlayerController::AActionPlayerController() {

	//El actor se replica para que se tenga en cuenta las modificaciones del servidor, por ejemplo el cambió de defaultPawn
	bReplicates = true;

	//Referencias a las classes de los distintos pawn que puede usar el usuario
	ConstructorHelpers::FClassFinder <APilotActionPawn> refPilotActionPawnBP(TEXT("/Game/Blueprints/Action/PilotActionPawn_BP"));
	pilotClass = refPilotActionPawnBP.Class;

	ConstructorHelpers::FClassFinder <AArtilleryActionPawn> refArtilleryActionPawnBP(TEXT("/Game/Blueprints/Action/ArtilleryActionPawn_BP"));
	artilleryClass = refArtilleryActionPawnBP.Class;

}


void AActionPlayerController::BeginPlay() {

	Super::BeginPlay();

	//Por defecto el usuario usarà un pawn de tipo PilotAction, en caso de no haver pawn por defecto gameMode usara defaultPawn de GameMode
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
		//Podemos hacer get de GameMode ya que sabemos que esto se ejecutara en el servidor, igualmente usamos un condicional por prevencion
		if (AActionGameMode* GameMode = Cast<AActionGameMode>(World->GetAuthGameMode()))
		{
			AActionPlayerController* controllerRef = this;

			//Muy importante destruir el Pawn assignado al PlayerController antes del RestartPlayer, ya que en caso contrario el restart no llamara GetDefaultPawnClassForController
			//sino que reusarà el existente
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
	//El cliente debe decidir que pawn quiere, de otra manera si usaramos otro metodo mas personalizado para elegir el pawn y el servidor también ejecuta esta instruccion todos tendrian el mismo pawn definido por el servidor
	if (IsLocalController())
	{
		ServerSetPlayerControllerPawn(pilotClass);

	}
}

void AActionPlayerController::SetArtillery_Implementation()
{
	//El cliente debe decidir que pawn quiere, de otra manera si usaramos otro metodo mas personalizado para elegir el pawn y el servidor también ejecuta esta instruccion todos tendrian el mismo pawn definido por el servidor
	if (IsLocalController())
	{
		ServerSetPlayerControllerPawn(artilleryClass);

	}
}


//parametro 0 hace pawn de playerController ser pilot, cualquier otro lo transforma en artillery
void AActionPlayerController::SetPlayerControllerPawn(int index)
{

	//No es necessario comprovar quien ejecuta esta función ya que en SetArtillery y setPawn ya se mira que sea en local

	if(index)
	{
		SetArtillery();
	}else
	{

		SetPilot();
	}
}


void AActionPlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AActionPlayerController, myPawn);
}

