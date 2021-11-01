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

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	virtual void Tick(float DeltaSeconds) override;

	void PitchCamera(float AxisValue);

	void YawCamera(float AxisValue);

	
protected:
	
	AActionCamera* myCamera;

	FVector2D cameraInput;
};
