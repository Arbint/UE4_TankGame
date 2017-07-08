// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TrackComponet.h"
#include "Tank.h"


void UTankMovementComponent::BeginPlay()
{
	Super::BeginPlay();
	InitializeTracks();
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	UE_LOG(LogTemp, Warning, TEXT("%s: Intend to move forward at: %f"), *(GetName()), Throw);
	if (LeftTrack && RightTrack)
	{
		LeftTrack->SetThrottle(Throw);
		RightTrack->SetThrottle(Throw);
	}
}

void UTankMovementComponent::InitializeTracks()
{
	if (GetTankOnwer())
	{
		LeftTrack = GetTankOnwer()->LeftTankTrack;
		RightTrack = GetTankOnwer()->RightTankTrack;
	}
}

ATank* UTankMovementComponent::GetTankOnwer()
{
	return (ATank*)GetOwner();
}
