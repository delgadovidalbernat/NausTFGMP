// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "ActionPawn.generated.h"

class AActionCamera;

UCLASS()
class NAUSTFGMP_API AActionPawn : public APawn
{
	GENERATED_BODY()

public:

	// Sets default values for this pawn's properties
	AActionPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Llamado cuando el actor abandona el juego
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Autodescriptivo
	AActionCamera* getActionCamera();

	//Spawn de la camera
	virtual void spawnDefaultCamera();

protected:

	AActionCamera* myCamera;

};
