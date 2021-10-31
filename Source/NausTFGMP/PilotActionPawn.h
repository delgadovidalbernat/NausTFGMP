// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActionPawn.h"
#include "PilotActionPawn.generated.h"

class UActionCameraComponent;
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
	
	UActionCameraComponent* getCamera();

protected:

	//Variable seteada en blueprints
	UPROPERTY(BlueprintReadWrite)
	UActionCameraComponent* myCamera;


private:


	
};
