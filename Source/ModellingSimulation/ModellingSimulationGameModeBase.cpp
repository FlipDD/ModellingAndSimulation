// Fill out your copyright notice in the Description page of Project Settings.


#include "ModellingSimulationGameModeBase.h"
#include "MainCharacterHUD.h"

AModellingSimulationGameModeBase::AModellingSimulationGameModeBase() : Super()
{
	// use our custom HUD class
	HUDClass = AMainCharacterHUD::StaticClass();
}

