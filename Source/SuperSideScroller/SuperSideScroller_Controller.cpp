// Fill out your copyright notice in the Description page of Project Settings.


#include "SuperSideScroller_Controller.h"
#include "MainMenuWidget.h"

void ASuperSideScroller_Controller::BeginPlay()
{
	Super::BeginPlay();

	if (BP_MainMenuWidget != nullptr) {
		MainMenuWidget = CreateWidget<UMainMenuWidget>(this, BP_MainMenuWidget);
		MainMenuWidget->AddToViewport();
	}
}

void ASuperSideScroller_Controller::ShowMainMenuWidget()
{
	if (BP_MainMenuWidget != nullptr) {
		SetPause(true);
		SetInputMode(FInputModeUIOnly());
		bShowMouseCursor = true;
		MainMenuWidget = CreateWidget<UMainMenuWidget>(this, BP_MainMenuWidget);
		MainMenuWidget->AddToViewport();
	}
}

void ASuperSideScroller_Controller::HideMainMenuWidget()
{
	MainMenuWidget->RemoveFromParent();
	MainMenuWidget->Destruct();

	SetPause(false);
	SetInputMode(FInputModeGameOnly());
	bShowMouseCursor = false;
}
