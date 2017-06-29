// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "Engine/World.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	TankBase = CreateDefaultSubobject<UStaticMeshComponent>("TankBase");
	TankTorret = CreateDefaultSubobject<UStaticMeshComponent>("TankTorrect");
	TankBarrel = CreateDefaultSubobject<UStaticMeshComponent>("TankBarrel");
	RootComponent = TankBase;
	TankTorret->SetupAttachment(RootComponent, TorretSocketName);
	TankBarrel->SetupAttachment(TankTorret, BarrelSocketName);
	TankBase->SetSimulatePhysics(true);
	TankBase->SetMassOverrideInKg(NAME_None, 40000.0f);
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>("CameraBoom");
	PlayerEye = CreateDefaultSubobject<UCameraComponent>("PlayerEye");
	CameraBoom->SetupAttachment(RootComponent);
	PlayerEye->SetupAttachment(CameraBoom);
	//CameraBoom->bUsePawnControlRotation = true;
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATank::LookUp(float amount)
{
	//AddControllerPitchInput(amount * GetWorld()->GetDeltaSeconds() * TankAimingSensitiviy);
	CameraBoom->AddLocalRotation(FRotator(0.0f, 0.0f, amount * GetWorld()->GetDeltaSeconds() * TankAimingSensitiviy));
}

void ATank::LookRight(float amount)
{
	//AddControllerYawInput(amount * GetWorld()->GetDeltaSeconds() * TankAimingSensitiviy);
	CameraBoom->AddLocalRotation(FRotator(0.0f,amount * GetWorld()->GetDeltaSeconds() * TankAimingSensitiviy ,0.0f));
}

