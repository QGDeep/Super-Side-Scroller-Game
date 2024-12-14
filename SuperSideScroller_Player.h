// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SuperSideScrollerCharacter.h"
#include "SuperSideScroller_Player.generated.h"

/**
 *
 */
UCLASS()
class SUPERSIDESCROLLER_API ASuperSideScroller_Player : public ASuperSideScrollerCharacter
{
	GENERATED_BODY()

	// Constructor
	ASuperSideScroller_Player();

protected:
	// Override base character class function to setup our player input component
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Called when player holds the sprint key - sprinting
	void Sprint();

	// Called when player releases the sprint key
	void StopSprinting();

	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputMappingContext* IC_Character;

	// Sprint input
	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputAction* IA_Sprint;

	// Throw input
	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputAction* IA_Throw;

	// Open main menu input
	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputAction* IA_OpenMenu;

	// Close main menu input
	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputAction* IA_CloseMenu;

	// Function for throwing
	void ThrowProjectile();

	// Handles when powerup effects end
	void EndPowerup();

public:

	// Function for spawning projectile
	void SpawnProjectile();

	// Function to get total collectables (getter)
	UFUNCTION(BlueprintPure)
	int32 GetCurrentNumberofCollectables() { return NumberofCollectables; };

	// Increase total number of collectables (used to keep track of collectables)
	void IncrementNumberofCollectables(int32 Value);

	// Increase player movement speed when powerup is collected
	void IncreaseMovementPowerup();

	// Handles opening and closing of main menu
	void OpenMainMenu();

	// Handles opening and closing of main menu
	void CloseMainMenu();

private:
	// Bool to control if we are sprinting (used as a failsafe)
	bool bIsSprinting;

	UPROPERTY(EditAnywhere)
	class UAnimMontage* ThrowMontage;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class APlayerProjectile> PlayerProjectile;

	// Track total collected coins
	int32 NumberofCollectables;

	// Timer handle for powerup
	FTimerHandle PowerupHandle;

	bool bHasPowerupActive;
};
