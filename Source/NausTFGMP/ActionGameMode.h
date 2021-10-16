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

	AActionGameMode();

	void InitializeDefaultPawnClass();

	virtual UClass* GetDefaultPawnClassForController_Implementation(AController* InController) override;

	virtual void RestartPlayer(AController* NewPlayer) override;

private:

	TSubclassOf<AActionPawn> pilotClass;
	
};
