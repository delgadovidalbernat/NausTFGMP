// Fill out your copyright notice in the Description page of Project Settings.


#include "ArtilleryActionPawn.h"

#include "Cameras/ActionCamera.h"

void AArtilleryActionPawn::spawnDefaultCamera()
{

	FVector spawnLocation = GetActorLocation();
	spawnLocation += GetActorForwardVector() * 1 + GetActorUpVector() * 1;

	FRotator spawnRotation = GetActorRotation();
	spawnRotation += FRotator(0.f, 0.f, 0.f);


	myCamera = GetWorld()->SpawnActor<AActionCamera>(spawnLocation, spawnRotation);

	myCamera->SetOwner(this);
}
