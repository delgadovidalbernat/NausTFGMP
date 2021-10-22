// Fill out your copyright notice in the Description page of Project Settings.


#include "PilotActionPawn.h"
#include "Cameras/ActionCamera.h"
#include "Net/UnrealNetwork.h"

APilotActionPawn::APilotActionPawn()
{


}

void APilotActionPawn::BeginPlay()
{
	Super::BeginPlay();
	//spawnDefaultCamera();

}

void APilotActionPawn::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if(myCamera)
		myCamera->Destroy();
	else
	{

		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "No es possible borrar una ActionCamera que no existe");
	}
}

AActionCamera* APilotActionPawn::getActionCamera()
{

	return myCamera;
}



void APilotActionPawn::spawnDefaultCamera()
{

	FVector spawnLocation = GetActorLocation();
	spawnLocation += GetActorForwardVector() * -300 + GetActorUpVector() * 150;

	FRotator spawnRotation = GetActorRotation();
	spawnRotation += FRotator(-30.f, 0.f, 0.f);

	myCamera = GetWorld()->SpawnActor<AActionCamera>(spawnLocation, spawnRotation);
}


