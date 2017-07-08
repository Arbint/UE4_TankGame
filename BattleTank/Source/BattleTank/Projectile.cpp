// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"
#include "UniversalFucs.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ProjectlieComp = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileComp");
	ProjectlieComp->bAutoActivate = false;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::launch(float launchSpeed)
{
	if (ProjectlieComp)
	{
		ProjectlieComp->SetActive(true);
		ProjectlieComp->SetVelocityInLocalSpace(FVector::ForwardVector * launchSpeed);
	}
	else
	{
		UUniversalFucs::ScreenMessage("No Projectile Component");
	}

}

