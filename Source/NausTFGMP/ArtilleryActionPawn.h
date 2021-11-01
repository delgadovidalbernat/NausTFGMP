// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActionPawn.h"
#include "ArtilleryActionPawn.generated.h"

/**
 * 
 */
UCLASS()
class NAUSTFGMP_API AArtilleryActionPawn : public AActionPawn
{
	GENERATED_BODY()


public:
	//spawn la camera de Artillery (era una opcion dejar esto para el controller, pero como cada pawn usa la camara de forma distinta hay que pensar-lo)
	virtual void spawnDefaultCamera() override;
};
