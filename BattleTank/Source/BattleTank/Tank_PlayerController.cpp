// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank_PlayerController.h"
#include "Engine/World.h"
#include "Tank.h"


ATank_PlayerController::ATank_PlayerController()
{

}

void ATank_PlayerController::BeginPlay()
{
	Super::BeginPlay();
	TankPossessed = (ATank*)GetPawn();
}

void ATank_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAxis("AimPitch", this, &ATank_PlayerController::LookUp);
	InputComponent->BindAxis("AimYaw", this, &ATank_PlayerController::LookRight);
}

void ATank_PlayerController::LookUp(float amount)
{
	if (TankPossessed)
	{
		TankPossessed->LookUp(amount);
	}

}

void ATank_PlayerController::LookRight(float amount)
{
	if (TankPossessed)
	{
		TankPossessed->LookRight(amount);
	}
}
