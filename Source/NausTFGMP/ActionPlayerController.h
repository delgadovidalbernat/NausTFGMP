// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ActionPlayerController.generated.h"

class ADefaultActionPawn;
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

	//Funcion que desde el cliente asignara a Pilot como Pawn del PlayerController  
	UFUNCTION(Client, Reliable)
	void SetDefaultActionPawn();
	void SetDefaultActionPawn_Implementation();


	//Funcion que desde el cliente asignara a Artillery como Pawn del PlayerController  
	UFUNCTION(Client, Reliable)
	void SetArtillery();
	void SetArtillery_Implementation();

	//Funcion que segun indice llama a setPilot o setArtillery
	UFUNCTION(Exec)
	void SetPlayerControllerPawn(int index);

	//Funcion que assiganarà a las variables replicadas las condiciones de replicacion
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	//Busca y guarda referencia al blueprint MainMenu_BP
	void InitializeMainMenuClass();

	//Busca y guarda referencia al blueprint InGameMenuClass
	void InitializeInGameMenuClass();

	//Busca y guarda referencia al blueprint PilotPawnClass
	void InitializePilotPawnClass();

	//Busca y guarda referencia al blueprint ArtillryPawnClass
	void InitializeArtillryPawnClass();

	//Busca y guarda referencia al blueprint DefaultActionPawnClass
	void InitializeDefaultActionPawnClass();

	//Agrupación de las tres funciones anteriores
	void InitializePawnClasses();

	//Despliega MainMenu en la pantalla
	void LoadMainMenu();

	//Elimina MainMenu de la pantalla
	UFUNCTION()
	void UnloadMainMenu();

	//Despliega InGameMenu en la pantalla
	UFUNCTION()
	void LoadInGameMenu();

	//Elimina InGameMenu de la pantalla
	UFUNCTION()
	void UnloadInGameMenu();

	//Muestra cursor en la pantalla y lo desbloquea
	void ShowNotLockingMouseCursor(UUserWidget* UIMenu);

	//Oculta cursor de la pantalla y lo bloquea
	void HideAndLockMouseCursor(UUserWidget* UIMenu);

	//Enlaza todas las signals de distintas classes con delegates a funciones del PC
	void BindSignals();

	//Crea widget que contiene MainMenu
	void CreaMainMenu();

	//Crea widget que contiene InGameMenu
	void CreaInGameMenu();

	//En el editor sale del modo PIE, en aplicación sale al escritorio
	UFUNCTION()
	void ExitGame();

	//Bincula inputs del usuario que se usarà en el controller, lo que no se controle aqui passara al inpout del pawn
	virtual void SetupInputComponent() override;

	//Se encarga de recoger la camara principal del pawn controlado y la usa
	void SetViewPawn(AActionPawn* myPilotPawn);

	//Se llama cada frame
	virtual void Tick(float DeltaSeconds) override;


private:

	//Pawn definitivo que el usuario usara, esta replicado ya que esta variable sera enviada al servidor y cuyando el servidor la modifique queremos que replique esa informacion al cliente
	UPROPERTY(Replicated)
	TSubclassOf<AActionPawn> myPawnClass;

	//Referencia a classes de possibles pawn entre las que el usuario puede escoger
	TSubclassOf<AActionPawn> pilotClass;
	TSubclassOf<AActionPawn> artilleryClass;
	TSubclassOf<AActionPawn> defaultActionPawnClass;

	//referencia a la classe blueprint de mainMenu
	TSubclassOf<UMainMenu_EP> mainMenuClass;

	//instancia de la clase mainMenu
	UPROPERTY()
	UMainMenu_EP* mainMenu;

	//referencia a la classe blueprint de inGameMenuClass
	TSubclassOf<UInGameMenu_EP> inGameMenuClass;

	//El uproperty se debe a que en caso de no ponerlo el engine piensa que no se usa y es recogido por el garbage collection, bueno saberlo despues de 3 horas buscando un error que no existe :)
	UPROPERTY()
	UInGameMenu_EP* inGameMenu;

	//refleja si el inGameMenu esta abierto
	bool isInGameMenuOpen;
	

};
