// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenu_EP.generated.h"

/**
 * 
 */
UCLASS()
class NAUSTFGMP_API UMainMenu_EP : public UUserWidget
{
	GENERATED_BODY()


public:

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnClickExit);
	FOnClickExit signalOnClickExit;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnClickPlay);
	FOnClickPlay signalOnClickPlay;


public:


	UFUNCTION(BlueprintCallable, Category = "Director", DisplayName = "OnCLickExit")
	void OnClickExitButton();

	UFUNCTION(BlueprintCallable, Category = "Director", DisplayName = "OnCLickPlay")
	void OnClickPlayButton();

};
