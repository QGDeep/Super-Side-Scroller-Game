// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"
#include "SuperSideScroller_Controller.h"

void UMainMenuWidget::OnRestartClicked()
{
	ASuperSideScroller_Controller* PlayerController = Cast<ASuperSideScroller_Controller>(GetOwningPlayer());
	if (PlayerController != nullptr) {
		PlayerController->HideMainMenuWidget();
	}

	UGameplayStatics::OpenLevel(this,
		FName(*UGameplayStatics::GetCurrentLevelName(this)));
}

void UMainMenuWidget::OnExitClicked()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, true);
}

void UMainMenuWidget::OnContinueClicked()
{
	ASuperSideScroller_Controller* PlayerController = Cast<ASuperSideScroller_Controller>(GetOwningPlayer());
	if (PlayerController != nullptr) {
		PlayerController->HideMainMenuWidget();
	}
}

void UMainMenuWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	/*ASuperSideScroller_Controller* PlayerController = Cast<ASuperSideScroller_Controller>(GetOwningPlayer());
	if (PlayerController != nullptr) {
		PlayerController->HideMainMenuWidget();
	}*/
	
	if (RestartButton != nullptr) {
		RestartButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnRestartClicked);
	}

	if (ExitButton != nullptr) {
		ExitButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnExitClicked);
	}

	if (ContinueButton != nullptr) {
		ContinueButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnContinueClicked);
	}
}
