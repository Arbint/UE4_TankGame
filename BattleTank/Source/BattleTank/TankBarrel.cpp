// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
#include "Engine/World.h"



void UTankBarrel::elevateBarrel(float relativeSpeed)
{
	auto clampedRelativeSpeed = FMath::Clamp(relativeSpeed, -1.0f, 1.0f);
	auto elevationChange = clampedRelativeSpeed * maxElevationSpeed * GetWorld()->GetDeltaSeconds();
	auto RawNewElevation = RelativeRotation.Pitch + elevationChange;
	auto ClampedElevation = FMath::Clamp(RawNewElevation, minElevationDegrees, maxElevationDegrees);
	SetRelativeRotation(FRotator(ClampedElevation, RelativeRotation.Yaw, RelativeRotation.Roll));
}

void UTankBarrel::spinBarrel(float relativeSpeed)
{
	if (!BaseTorret) { return; }
	relativeSpeed = FMath::Clamp(relativeSpeed, -1.0f, 1.0f);
	auto YawIncrement = relativeSpeed * maxSpinSpeed * GetWorld()->GetDeltaSeconds();
	BaseTorret->AddLocalRotation(FRotator(0.0f, YawIncrement, 0.0f));
}

void UTankBarrel::setBaseTorret(UStaticMeshComponent* BaseTorretToSet)
{
	BaseTorret = BaseTorretToSet;
}

