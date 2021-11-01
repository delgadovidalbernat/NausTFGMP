// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionPawn.h"

#include "Cameras/ActionCamera.h"

// Sets default values
AActionPawn::AActionPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AActionPawn::BeginPlay()
{
	Super::BeginPlay();

	spawnDefaultCamera();
}

void AActionPawn::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (myCamera)
		myCamera->Destroy();
	else
	{

		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "No es possible borrar una ActionCamera que no existe");
	}
}

// Called every frame
void AActionPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AActionPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	
}

AActionCamera* AActionPawn::getActionCamera()
{

	return myCamera;
}

void AActionPawn::spawnDefaultCamera()
{

	FVector spawnLocation = GetActorLocation();
	spawnLocation += GetActorForwardVector() * -300 + GetActorUpVector() * 150;

	FRotator spawnRotation = GetActorRotation();
	spawnRotation += FRotator(-30.f, 0.f, 0.f);


	myCamera = GetWorld()->SpawnActor<AActionCamera>(spawnLocation, spawnRotation);

	myCamera->SetOwner(this);
	
}

