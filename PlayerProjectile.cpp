// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "EnemyBase.h"
#include "Components/AudioComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APlayerProjectile::APlayerProjectile()
{
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(15.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("BlockAll");
	CollisionComp->OnComponentHit.AddDynamic(this, &APlayerProjectile::OnHit);

	// Set collision component as root component
	RootComponent = CollisionComp;

	// Use projectile movement component to control this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->ProjectileGravityScale = 0.0f;
	ProjectileMovement->InitialSpeed = 800.0f;
	ProjectileMovement->MaxSpeed = 800.0f;

	// Setup mesh component
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh-Comp"));
	MeshComp->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);

	// Setup projectile movement sound
	ProjectileMovementSound = CreateDefaultSubobject<UAudioComponent>(TEXT("ProjectileMovementSound"));
	ProjectileMovementSound->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);

	// Setup projectile effects
	ProjectileEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ProjectileEffect"));
	ProjectileEffect->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);

	InitialLifeSpan = 3.0f;
}

void APlayerProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// UE_LOG(LogTemp, Warning, TEXT("HIT"));

	// Create new enemy variable and cast as other actor
	AEnemyBase* Enemy = Cast<AEnemyBase>(OtherActor);
	if (Enemy) {
		Enemy->DestroyEnemy();
	}
	ExplodeProjectile();
}

void APlayerProjectile::ExplodeProjectile()
{
	Destroy();
	UWorld* World = GetWorld();
	if (World) {
		if (DestroyEffect) {
			UGameplayStatics::SpawnEmitterAtLocation(World, DestroyEffect, GetActorTransform());
		}
		if (DestroySound) {
			UGameplayStatics::SpawnSoundAtLocation(World, DestroySound, GetActorLocation());
		}
	}
}
