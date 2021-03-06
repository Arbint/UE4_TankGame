// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "AimingComponent.h"
#include "Engine/World.h"
#include "TankBarrel.h"
#include "UniversalFucs.h"
#include "Projectile.h"
#include "TrackComponet.h"
#include "TankMovementComponent.h"
// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	TankBase = CreateDefaultSubobject<UStaticMeshComponent>("TankBase");
	TankTorret = CreateDefaultSubobject<UStaticMeshComponent>("TankTorrect");
	Barrel = CreateDefaultSubobject<UTankBarrel>("TankBarrel");
	LeftTankTrack = CreateDefaultSubobject<UTrackComponet>("LeftTankTrack");
	RightTankTrack = CreateDefaultSubobject<UTrackComponet>("RightTankTrack");
	RootComponent = TankBase;
	TankTorret->SetupAttachment(RootComponent, TorretSocketName);
	LeftTankTrack->SetupAttachment(RootComponent);
	RightTankTrack->SetupAttachment(RootComponent);
	Barrel->SetupAttachment(TankTorret, BarrelSocketName);
	TankBase->SetSimulatePhysics(true);
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>("CameraBoom");
	CameraBoomAzimuthGimbal = CreateDefaultSubobject<USceneComponent>("CameraBoomAzimuthGimbal");
	CameraBoomAzimuthGimbal->SetupAttachment(RootComponent);
	PlayerEye = CreateDefaultSubobject<UCameraComponent>("PlayerEye");
	CameraBoom->SetupAttachment(CameraBoomAzimuthGimbal);
	CameraBoom->bInheritRoll = false;
	PlayerEye->SetupAttachment(CameraBoom);

	//CameraBoom->bUsePawnControlRotation = true;
	AimingComponent = CreateDefaultSubobject<UAimingComponent>("AimingComponent");
	MovementComponent = CreateDefaultSubobject<UTankMovementComponent>("MovementComponent");
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	TankBase->SetMassOverrideInKg(NAME_None, 40000.0f);
	SetupFirePointToAimComp(Barrel);
	Barrel->setBaseTorret(TankTorret);
	LastFireTime = -ProjectileLodingTime;
}



// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATank::LookUp(float amount)
{
	//AddControllerPitchInput(amount * GetWorld()->GetDeltaSeconds() * TankAimingSensitiviy);
	CameraBoom->AddLocalRotation(FRotator(amount * GetWorld()->GetDeltaSeconds() * TankAimingSensitiviy,0.0f, 0.0f));
	
	//Clamp the rotation
	float CameraBoomPitch = FMath::Clamp(CameraBoom->GetRelativeTransform().Rotator().Pitch,-90.f, 90.0f);
	CameraBoom->SetRelativeRotation(FRotator(
		FMath::Clamp(CameraBoom->GetRelativeTransform().Rotator().Pitch, -75.f, 75.0f),
		FMath::Clamp(CameraBoom->GetRelativeTransform().Rotator().Yaw, -75.f, 75.0f),
		FMath::Clamp(CameraBoom->GetRelativeTransform().Rotator().Roll, -75.f, 75.0f)));
}

void ATank::LookRight(float amount)
{
	//AddControllerYawInput(amount * GetWorld()->GetDeltaSeconds() * TankAimingSensitiviy);
	CameraBoomAzimuthGimbal->AddLocalRotation(FRotator(0.0f,amount * GetWorld()->GetDeltaSeconds() * TankAimingSensitiviy ,0.0f));
}

void ATank::AimAt(FVector location)
{
	AimingComponent->AimingAt(location, LaunchingSpeed);
}

void ATank::SetupFirePointToAimComp(UTankBarrel* FiringPointToSet)
{
	if (AimingComponent)
	{
		AimingComponent->SetFiringPoint(FiringPointToSet);
	}
}

void ATank::NurtualAim()
{
	AimingComponent->nurtualAiming();
}

void ATank::Fire()
{
	bool bIsLoaded = (GetWorld()->GetTimeSeconds() - LastFireTime) >= ProjectileLodingTime;
	if (Barrel && bIsLoaded)
	{
		FActorSpawnParameters ProjectileSpawnPrams;
		
		auto projectileFired = GetWorld()->SpawnActor<AProjectile>(
			ProjectTileToFire, 
			Barrel->GetSocketLocation("FiringPoint"),
			Barrel->GetSocketRotation("FiringPoint"),
			ProjectileSpawnPrams);
		if (projectileFired)
		{
			projectileFired->launch(LaunchingSpeed);
		}
		LastFireTime = GetWorld()->GetTimeSeconds();
	}
}

void ATank::SetTrackthrottle(UTrackComponet* tracToSet, float amount)
{
	tracToSet->SetThrottle(amount);
}

void ATank::MoveForward(float amount)
{
	MovementComponent->IntendMoveForward(amount);
}

