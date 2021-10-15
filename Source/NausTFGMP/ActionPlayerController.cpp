// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionPlayerController.h"
#include "PilotActionPawn.h"

AActionPlayerController::AActionPlayerController() {

	ConstructorHelpers::FClassFinder <APilotActionPawn> refBlueprint(TEXT("/Game/Blueprints/Action/PilotActionPawn_BP"));
	pilotClass = refBlueprint.Class;
}


void AActionPlayerController::BeginPlay() {

	Super::BeginPlay();

	APilotActionPawn* pilot = GetWorld()->SpawnActor<APilotActionPawn>(pilotClass);
	Possess(pilot);

}