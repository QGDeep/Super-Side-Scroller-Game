// Fill out your copyright notice in the Description page of Project Settings.


#include "PickableActor_Collectable.h"
#include "SuperSideScroller_Player.h"

void APickableActor_Collectable::BeginPlay()
{
	// Make super call to parent class function of the same name
	Super::BeginPlay();
}

void APickableActor_Collectable::PlayerPickedUp(ASuperSideScroller_Player* Player)
{
	// Call the increment collectable function from player
	Player->IncrementNumberofCollectables(CollectableValue);
	// Make super call to parent class function of the same name
	Super::PlayerPickedUp(Player);
}
