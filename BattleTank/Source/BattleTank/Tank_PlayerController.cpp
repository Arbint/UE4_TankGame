// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank_PlayerController.h"
#include "Engine/World.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Tank.h"


ATank_PlayerController::ATank_PlayerController()
{
	
}

void ATank_PlayerController::BeginPlay()
{
	Super::BeginPlay();
	TankPossessed = GetControlledTank();
}

void ATank_PlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	AimAtCrossHair();
}

void ATank_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAxis("AimPitch", this, &ATank_PlayerController::LookUp);
	InputComponent->BindAxis("AimYaw", this, &ATank_PlayerController::LookRight);
	InputComponent->BindAction("QuitGame", IE_Pressed, this, &ATank_PlayerController::QuitGame);
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

ATank* ATank_PlayerController::GetControlledTank()
{
	return (ATank*)GetPawn();
}



void ATank_PlayerController::QuitGame()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), this, EQuitPreference::Quit);
}

void ATank_PlayerController::AimAtCrossHair()
{
	if (GetControlledTank())
	{
		FHitResult hit;
		if (LineTraceThroughCrosshair(hit))
		{
			FString HitObjectName = hit.GetActor()->GetName();
			UE_LOG(LogTemp, Warning, TEXT("Hit Object is: %s"), *HitObjectName);
		}
	}
}

FVector2D ATank_PlayerController::GetCrossHairScreenLocation()
{
	int32 ViewPortSizeX;
	int32 ViewPortSizeY;
	GetViewportSize(ViewPortSizeX, ViewPortSizeY);
	return FVector2D(ViewPortSizeX * crossHairXLocation, ViewPortSizeY * crossHairYLocation);
}

bool ATank_PlayerController::GetCrossHairLookDirection(FVector2D ScreeLocation, FVector& LookDirection)
{
	FVector CorssHairOverLappyingLocation;
	return	DeprojectScreenPositionToWorld(
		ScreeLocation.X, 
		ScreeLocation.Y, 
		CorssHairOverLappyingLocation, 
		LookDirection);
}

bool ATank_PlayerController::LineTraceThroughCrosshair(FHitResult &outHit)
{
	FVector CrossHairLookDirection;
	GetCrossHairLookDirection(GetCrossHairScreenLocation(), CrossHairLookDirection);
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (CrossHairLookDirection * sightReach);
	
	bool bIsHitingByTracing = GetWorld()->LineTraceSingleByChannel(
		outHit,
		StartLocation,
		EndLocation,
		ECC_Visibility
	);
	return bIsHitingByTracing;
}

