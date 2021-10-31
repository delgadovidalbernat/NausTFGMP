// Fill out your copyright notice in the Description page of Project Settings.


#include "PilotActionPawn.h"
#include "Cameras/ActionCameraComponent.h"
#include "Net/UnrealNetwork.h"


APilotActionPawn::APilotActionPawn()
{
	bReplicates = true;
	
}

void APilotActionPawn::BeginPlay()
{
	Super::BeginPlay();


}

UActionCameraComponent* APilotActionPawn::getCamera()
{

	return myCamera;
}

