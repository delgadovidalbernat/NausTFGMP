// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActionPawn.h"
#include "PilotActionPawn.generated.h"

class AActionCamera;
/**
 * 
 */
UCLASS()
class NAUSTFGMP_API APilotActionPawn : public AActionPawn
{
	GENERATED_BODY()

public:

	APilotActionPawn();

	virtual void BeginPlay() override;

	
protected:
	
	AActionCamera* myCamera;
};
