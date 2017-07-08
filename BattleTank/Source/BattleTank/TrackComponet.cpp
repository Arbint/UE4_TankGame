// Fill out your copyright notice in the Description page of Project Settings.

#include "TrackComponet.h"




void UTrackComponet::SetThrottle(float amount)
{

	auto forceApplied = GetForwardVector() * amount * TrackMaxDrivingForce;
	auto forceLocation = GetComponentLocation();
	auto TankRoot = (UPrimitiveComponent*)GetOwner()->GetRootComponent();
	TankRoot->AddForceAtLocation(forceApplied, forceLocation);
}
