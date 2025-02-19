// Fill out your copyright notice in the Description page of Project Settings.


#include "SuperSideScroller_Brick.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "SuperSideScroller_Player.h"

// Sets default values
ASuperSideScroller_Brick::ASuperSideScroller_Brick()
{
	// Set BrickMesh, its collision profile and set as root component
	BrickMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BrickMesh"));
	BrickMesh->SetCollisionProfileName("BlockAll");
	RootComponent = BrickMesh;

	// Setup brick collision, its collision profile and attach to root component
	BrickCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BrickCollision"));
	BrickCollision->SetCollisionProfileName("BlockAll");
	BrickCollision->AttachToComponent(RootComponent,
		FAttachmentTransformRules::KeepWorldTransform);

	// Assign OnHit function to brick collision (Box Components OnHitComponent callback)
	BrickCollision->OnComponentHit.AddDynamic(this, &ASuperSideScroller_Brick::OnHit);
}

void ASuperSideScroller_Brick::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	ASuperSideScroller_Player* Player = Cast<ASuperSideScroller_Player>(OtherActor);
	if (Player && bHasCollectable) {
		AddCollectable(Player);
		PlayHitSound();
		PlayHitExplosion();
		Destroy();
	}
}

void ASuperSideScroller_Brick::AddCollectable(ASuperSideScroller_Player* Player)
{
	Player->IncrementNumberofCollectables(CollectableValue);
}

void ASuperSideScroller_Brick::PlayHitSound()
{
	UWorld* World = GetWorld();
	if (World && HitSound) {
		UGameplayStatics::SpawnSoundAtLocation(World, HitSound, GetActorLocation());
	}
}

void ASuperSideScroller_Brick::PlayHitExplosion()
{
	UWorld* World = GetWorld();
	if (World && Explosion) {
		UGameplayStatics::SpawnEmitterAtLocation(World, Explosion, GetActorTransform());
	}
}

// Called when the game starts or when spawned
void ASuperSideScroller_Brick::BeginPlay()
{
	Super::BeginPlay();

}
