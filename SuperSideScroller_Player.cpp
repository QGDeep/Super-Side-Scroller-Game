// Fill out your copyright notice in the Description page of Project Settings.


#include "SuperSideScroller_Player.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Animation/AnimInstance.h"
#include "PlayerProjectile.h"
#include "Engine/World.h"
#include "Components/SphereComponent.h"
#include "TimerManager.h"
#include "SuperSideScroller_Controller.h"

ASuperSideScroller_Player::ASuperSideScroller_Player() {

	// Init bISprinting to false as default value
	bIsSprinting = false;

	// Set max character walk speed to 300.0f as default value
	GetCharacterMovement()->MaxWalkSpeed = 300.0f;
}

void ASuperSideScroller_Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	//Not always necessary, but good practice to call the
	//function in the base class with Super.
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedPlayerInput = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	// Check if enhanced input component is valid
	if (EnhancedPlayerInput) {
		// get reference to player controller to access local player subsystem
		// and assign mapping context
		APlayerController* PlayerController = Cast<APlayerController>(GetController());

		UEnhancedInputLocalPlayerSubsystem* EnhancedSubsystem =
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());

		if (EnhancedSubsystem) {
			EnhancedSubsystem->AddMappingContext(IC_Character, 1);
		}

		// Bind sprint action (when pressed)
		EnhancedPlayerInput->BindAction(IA_Sprint, ETriggerEvent::Triggered, this, &ASuperSideScroller_Player::Sprint);

		// Bind stop sprint action (when released)
		EnhancedPlayerInput->BindAction(IA_Sprint, ETriggerEvent::Completed, this, &ASuperSideScroller_Player::StopSprinting);

		// Bind throw action
		EnhancedPlayerInput->BindAction(IA_Throw, ETriggerEvent::Triggered, this, &ASuperSideScroller_Player::ThrowProjectile);

		// Bind open menu action
		EnhancedPlayerInput->BindAction(IA_OpenMenu, ETriggerEvent::Triggered, this, &ASuperSideScroller_Player::OpenMainMenu);

		// Bind close menu action
		EnhancedPlayerInput->BindAction(IA_CloseMenu, ETriggerEvent::Triggered, this, &ASuperSideScroller_Player::CloseMainMenu);
	}
}

void ASuperSideScroller_Player::Sprint()
{
	if (!bIsSprinting) {
		bIsSprinting = true;
		if (bHasPowerupActive) {
			GetCharacterMovement()->MaxWalkSpeed = 900.0f;
		}
		else {
			GetCharacterMovement()->MaxWalkSpeed = 500.0f;
		}
	}
}

void ASuperSideScroller_Player::StopSprinting()
{
	if (bIsSprinting) {
		bIsSprinting = false;
		if (bHasPowerupActive) {
			GetCharacterMovement()->MaxWalkSpeed = 500.0f;
		}
		else {
			GetCharacterMovement()->MaxWalkSpeed = 300.0f;
		}
	}
}

void ASuperSideScroller_Player::ThrowProjectile()
{
	// UE_LOG(LogTemp, Warning, TEXT("THROW PROJECTILE"));

	// check if throw montage is valid
	if (ThrowMontage) {
		const bool bIsMontagePlaying = GetMesh()->GetAnimInstance()->Montage_IsPlaying(ThrowMontage);

		if (!bIsMontagePlaying) {
			GetMesh()->GetAnimInstance()->Montage_Play(ThrowMontage, 1.0f);
		}
	}
}

void ASuperSideScroller_Player::EndPowerup()
{
	bHasPowerupActive = false;

	GetCharacterMovement()->MaxWalkSpeed = 300.0f;
	GetCharacterMovement()->JumpZVelocity = 1000.0f;

	UWorld* World = GetWorld();
	if (World) {
		World->GetTimerManager().ClearTimer(PowerupHandle);
	}
}

void ASuperSideScroller_Player::OpenMainMenu()
{
	ASuperSideScroller_Controller* MenuController = Cast<ASuperSideScroller_Controller>(GetController());
	if (MenuController != nullptr) {
		MenuController->ShowMainMenuWidget();
	}
}

void ASuperSideScroller_Player::CloseMainMenu()
{
	ASuperSideScroller_Controller* MenuController = Cast<ASuperSideScroller_Controller>(GetController());
	if (MenuController != nullptr) {
		MenuController->HideMainMenuWidget();
	}
}

void ASuperSideScroller_Player::SpawnProjectile()
{
	// check if player projectile in valid
	if (PlayerProjectile) {
		UWorld* World = GetWorld();
		// check if world is valid
		if (World) {
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;

			const FVector SpawnLocation = this->GetMesh()->GetSocketLocation(FName("ProjectileSocket"));
			const FRotator Rotation = GetActorForwardVector().Rotation();

			APlayerProjectile* Projectile = World->SpawnActor<APlayerProjectile>(PlayerProjectile, SpawnLocation, Rotation, SpawnParams);
		}
	}
}

// Increase total number of collectables (used to keep track of collectables)
void ASuperSideScroller_Player::IncrementNumberofCollectables(int32 Value)
{
	// If no collectables are collected
	if (Value == 0) {
		return;
	}
	else {
		NumberofCollectables += Value;
		// Send total number for debugging
		UE_LOG(LogTemp, Warning, TEXT("Number of Coins: %d"), NumberofCollectables);
	}
}

void ASuperSideScroller_Player::IncreaseMovementPowerup()
{
	// Set powerup active to true
	bHasPowerupActive = true;

	// Change walk speed and jump height
	GetCharacterMovement()->MaxWalkSpeed = 500.0f;
	GetCharacterMovement()->JumpZVelocity = 1500.0f;

	UWorld* World = GetWorld();
	if (World) {
		// Set timer for powerup when it is active
		World->GetTimerManager().SetTimer(PowerupHandle, this,
			&ASuperSideScroller_Player::EndPowerup, 8.0f, false);
	}
}
