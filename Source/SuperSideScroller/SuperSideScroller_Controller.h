// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SuperSideScroller_Controller.generated.h"

/**
 *
 */
UCLASS()
class SUPERSIDESCROLLER_API ASuperSideScroller_Controller : public APlayerController
{
	GENERATED_BODY()

private:
	UPROPERTY()
	class UMainMenuWidget* MainMenuWidget;

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UMainMenuWidget> BP_MainMenuWidget;

	void ShowMainMenuWidget();
	void HideMainMenuWidget();
};
