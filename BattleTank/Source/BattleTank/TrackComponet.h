// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TrackComponet.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTrackComponet : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	void SetThrottle(float amount);
	
	// Max force per track in Newtons
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float TrackMaxDrivingForce = 400000;
	
};
