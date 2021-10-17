// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "ActionGameMode.generated.h"

class AActionPawn;
/**
 * 
 */
UCLASS()
class NAUSTFGMP_API AActionGameMode : public AGameMode
{
	GENERATED_BODY()

public:

	//Constructora
	AActionGameMode();

	//Funcion que se llama para saber el Pawn assignado al playerController cuando no se especifica DefaultPawn en GameMode
	//Modificada para devolver el pawn que nos interese desde playerController
	//LLamada en RestartPlayer para hacer respawn del pawn siempre y cuandop el Pawn assignado a PLayerController sea null
	virtual UClass* GetDefaultPawnClassForController_Implementation(AController* InController) override;

	//Funcion que hace respawn del pawn del PlayerController, llama a GetDefaultPawnClassForController cuando este es nullptr
	virtual void RestartPlayer(AController* NewPlayer) override;

private:

	
};
