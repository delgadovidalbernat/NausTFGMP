// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ActionPlayerController.generated.h"

class AActionCamera;
class UInGameMenu_EP;
class AArtilleryActionPawn;
class AActionPawn;
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

	//Constructora
	AActionPlayerController();

	//Funci�n llamada cuando el actor est� listo para trabajar
	virtual void BeginPlay() override;

	//Funci�n que retorna el pawn escogido por el usuario
	UClass* GetPlayerPawnClass();

	
	//FRuncion que ejecuta el servidor y enviada por el cliente para que el servidor sepa que pawn quiere usar el usuario(el contenido de pawn ser� validado en el servidor para que este entre las possibles opciones)
	UFUNCTION(Server, Reliable, WithValidation)
	void ServerSetPlayerControllerPawn(TSubclassOf<AActionPawn> MyPawnClass);
	void ServerSetPlayerControllerPawn_Implementation(TSubclassOf<AActionPawn> MyPawnClass);
	bool ServerSetPlayerControllerPawn_Validate(TSubclassOf<AActionPawn> MyPawnClass);

	//Funcion que desde el cliente asignara a Pilot como Pawn del PlayerController  
	UFUNCTION(Client, Reliable)
	void SetPilot();
	void SetPilot_Implementation();

	//Funcion que desde el cliente asignara a Artillery como Pawn del PlayerController  
	UFUNCTION(Client, Reliable)
	void SetArtillery();
	void SetArtillery_Implementation();

	//Funcion que segun indice llama a setPilot o setArtillery
	UFUNCTION(Exec)
	void SetPlayerControllerPawn(int index);

	//Funcion que assiganarà a las variables replicadas las condiciones de replicacion
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	void InitializeMainMenuClass();

	void InitializeInGameMenuClass();

	void InitializePilotPawnClass();

	void LoadMainMenu();

	UFUNCTION()
	void UnloadMainMenu();

	UFUNCTION()
	void LoadInGameMenu();

	UFUNCTION()
	void UnloadInGameMenu();

	void ShowNotLockingMouseCursor(UUserWidget* UIMenu);

	void HideAndLockMouseCursor(UUserWidget* UIMenu);

	void BindSignals();

	void CreaMainMenu();

	void CreaInGameMenu();

	UFUNCTION()
	void ExitGame();

	virtual void SetupInputComponent() override;
	
	void SetViewPilot();

	
	virtual void OnPossess(APawn* InPawn) override;

private:

	//Pawn definitivo que el usuario usara, esta replicado ya que esta variable sera enviada al servidor y cuyando el servidor la modifique queremos que replique esa informacion al cliente
	UPROPERTY(Replicated)
	TSubclassOf<AActionPawn> myPawnClass;

	AActionPawn* myPawn;

	//Referencia a classes de possibles pawn entre las que el usuario puede escoger
	TSubclassOf<APilotActionPawn> pilotClass;
	TSubclassOf<AArtilleryActionPawn> artilleryClass;

	TSubclassOf<UMainMenu_EP> mainMenuClass;
	UPROPERTY()
	UMainMenu_EP* mainMenu;

	TSubclassOf<UInGameMenu_EP> inGameMenuClass;
	//El uproperty se debe a que en caso de no ponerlo el engine piensa que no se usa y es recogido por el garbage collection, bueno saberlo despues de 3 horas buscando un error que no existe :)
	UPROPERTY()
	UInGameMenu_EP* inGameMenu;

	bool isInGameMenuOpen;

};
