// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameMenu_EP.h"


void UInGameMenu_EP::OnClickExit()
{

	signalOnClickExit.Broadcast();
}

void UInGameMenu_EP::OnClickBack()
{

	signalOnClickBack.Broadcast();
}

void UInGameMenu_EP::OnClickUsePilotAsPlayerControllerPawn()
{

	signalOnClickUsePilotAsPlayerControllerPawn.Broadcast();
}

void UInGameMenu_EP::OnClickUseArtilleryAsPlayerControllerPawn()
{

	signalOnClickUseArtilleryAsPlayerControllerPawn.Broadcast();
}

