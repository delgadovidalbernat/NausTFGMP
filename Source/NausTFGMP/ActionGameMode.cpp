// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionGameMode.h"

AActionGameMode::AActionGameMode() {

	DefaultPawnClass = nullptr;
	PlayerControllerClass = AExplorationPlayerController::StaticClass();
	PlayerStateClass = AExplorationPlayerState::StaticClass();

}