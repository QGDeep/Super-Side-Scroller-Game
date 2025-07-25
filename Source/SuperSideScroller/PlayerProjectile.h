// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayerProjectile.generated.h"

UCLASS()
class SUPERSIDESCROLLER_API APlayerProjectile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APlayerProjectile();

	// Sphere collision component
	UPROPERTY(VisibleAnywhere, Category = Projectile)
	class USphereComponent* CollisionComp;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	void ExplodeProjectile();

private:
	// Projectile movement component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	class UProjectileMovementComponent* ProjectileMovement;

	// Static mesh component
	UPROPERTY(EditAnywhere, Category = Projectile)
	class UStaticMeshComponent* MeshComp;

	// Audio component for projectile
	UPROPERTY(VisibleDefaultsOnly, Category = Sound)
	class UAudioComponent* ProjectileMovementSound;

	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
	class UParticleSystemComponent* ProjectileEffect;

	// Effect to play when projectile collides
	UPROPERTY(EditAnywhere, Category = Projectile)
	class UParticleSystem* DestroyEffect;

	// Audio to play when projectile collides
	UPROPERTY(EditAnywhere, Category = Sound)
	class USoundBase* DestroySound;
};
