// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu_EP.h"

void UMainMenu_EP::OnClickExitButton()
{

	signalOnClickExit.Broadcast();
}

void UMainMenu_EP::OnClickPlayButton()
{

	signalOnClickPlay.Broadcast();
	
}
