// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionCamera.h"

AActionCamera::AActionCamera()
{

	if(GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Camera Lista");

	
}
