// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SuperSideScroller_Brick.generated.h"

UCLASS()
class SUPERSIDESCROLLER_API ASuperSideScroller_Brick : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleDefaultsOnly, Category = Brick)
	class UStaticMeshComponent* BrickMesh;

	// Box component for collision
	UPROPERTY(VisibleDefaultsOnly, Category = Brick)
	class UBoxComponent* BrickCollision;

	// Function to check box collision
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, FVector NormalImpulse,
		const FHitResult& Hit);

	// Check whether the brick contains collectable
	UPROPERTY(EditAnywhere)
	bool bHasCollectable;

	// Default value of collectable
	UPROPERTY(EditAnywhere)
	int32 CollectableValue = 1;

	// Function to add the collectable to the player
	void AddCollectable(class ASuperSideScroller_Player* Player);

	// Functions to access the HitSound and Explosion properties
	void PlayHitSound();

	void PlayHitExplosion();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Sets default values for this actor's properties
	ASuperSideScroller_Brick();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Brick)
	class USoundBase* HitSound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Brick)
	class UParticleSystem* Explosion;
};
