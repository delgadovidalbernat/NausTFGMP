// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ActionPlayerController.generated.h"

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


private:

	TSubclassOf<APilotActionPawn> pilotClass;
	
};
