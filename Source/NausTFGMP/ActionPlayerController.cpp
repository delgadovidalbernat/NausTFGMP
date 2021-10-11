// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionPlayerController.h"
#include "PilotActionPawn.h"

AActionPlayerController::AActionPlayerController() {

	ConstructorHelpers::FClassFinder <APilotActionPawn> refBlueprint(TEXT("/Game/Blueprints/Action/PilotActionPawn_BP"));
	pilotClass = refBlueprint.Class;
}


void AActionPlayerController::BeginPlay() {

	Super::BeginPlay();

	//El playerController local no ha de poder spawnejar ni posseir res, el PC del servidor fa aquestes accions i ho replica al client
	if (HasAuthority())
	{
		//Crea dos localitzacions properes pero random per veure com es fa spawn de + d'un client
		FVector spawnPosition(FMath::Rand()%200, 0.f, 100.f);
		FRotator spawnRotation(0.f, 0.f, 0.f);
		FActorSpawnParameters actorSpawnParameters;

		APilotActionPawn* pilot = GetWorld()->SpawnActor<APilotActionPawn>(pilotClass,spawnPosition, spawnRotation, actorSpawnParameters);
		Possess(pilot);

	}
	

}