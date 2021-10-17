// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InGameMenu_EP.generated.h"

/**
 * 
 */
UCLASS()
class NAUSTFGMP_API UInGameMenu_EP : public UUserWidget
{
	GENERATED_BODY()


public:

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnClickExit);
	FOnClickExit signalOnClickExit;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnClickBack);
	FOnClickExit signalOnClickBack;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnClickUsePilotAsPlayerControllerPawn);
	FOnClickUsePilotAsPlayerControllerPawn signalOnClickUsePilotAsPlayerControllerPawn;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnClickUseArtilleryAsPlayerControllerPawn);
	FOnClickUseArtilleryAsPlayerControllerPawn signalOnClickUseArtilleryAsPlayerControllerPawn;

	UFUNCTION(BlueprintCallable, Category = "Director", DisplayName = "OnCLickExit")
	void OnClickExit();

	UFUNCTION(BlueprintCallable, Category = "Director", DisplayName = "OnCLickBack")
	void OnClickBack();

	UFUNCTION(BlueprintCallable, Category = "Director", DisplayName = "OnClickUsePilotAsPlayerControllerPawn")
	void OnClickUsePilotAsPlayerControllerPawn();

	UFUNCTION(BlueprintCallable, Category = "Director", DisplayName = "OnClickUseArtilleryAsPlayerControllerPawn")
	void OnClickUseArtilleryAsPlayerControllerPawn();




};
