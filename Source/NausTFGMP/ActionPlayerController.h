// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ActionPlayerController.generated.h"

class AArtilleryActionPawn;
class AActionPawn;
class APilotActionPawn;

/**
 * 
 */
UCLASS()
class NAUSTFGMP_API AActionPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	AActionPlayerController();

	virtual void BeginPlay() override;

	UClass* GetPlayerPawnClass();

	

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerSetPlayerControllerPawn(TSubclassOf<AActionPawn> MyPawnClass);
	void ServerSetPlayerControllerPawn_Implementation(TSubclassOf<AActionPawn> MyPawnClass);
	bool ServerSetPlayerControllerPawn_Validate(TSubclassOf<AActionPawn> MyPawnClass);

	UFUNCTION(Client, Reliable)
	void SetPilot();
	void SetPilot_Implementation();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;


private:

	UPROPERTY(Replicated)
	TSubclassOf<AActionPawn> myPawn;

	TSubclassOf<APilotActionPawn> pilotClass;
	TSubclassOf<AArtilleryActionPawn> artilleryClass;
	
};
