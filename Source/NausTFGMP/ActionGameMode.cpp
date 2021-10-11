// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionGameMode.h"
#include "ActionGameState.h"
#include "ActionPlayerController.h"
#include "ActionPlayerState.h"

AActionGameMode::AActionGameMode() {

	DefaultPawnClass = nullptr;
	GameStateClass = AActionGameState::StaticClass();
	PlayerControllerClass = AActionPlayerController::StaticClass();
	PlayerStateClass = AActionPlayerState::StaticClass();

}