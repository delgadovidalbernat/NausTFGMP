// Fill out your copyright notice in the Description page of Project Settings.


#include "PilotActionPawn.h"
#include "Cameras/ActionCamera.h"
#include "Net/UnrealNetwork.h"

APilotActionPawn::APilotActionPawn()
{

	bReplicates = true;
}

void APilotActionPawn::BeginPlay()
{
	Super::BeginPlay();

}

void APilotActionPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis("CameraPitch", this, &APilotActionPawn::PitchCamera);
	InputComponent->BindAxis("CameraYaw", this, &APilotActionPawn::YawCamera);

}

void APilotActionPawn::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	FRotator NewRotation = GetActorRotation();
	NewRotation.Yaw += cameraInput.X;
	SetActorRotation(NewRotation);

}

void APilotActionPawn::PitchCamera(float AxisValue)
{

	cameraInput.Y = AxisValue;
}

void APilotActionPawn::YawCamera(float AxisValue)
{

	cameraInput.X = AxisValue;
}





