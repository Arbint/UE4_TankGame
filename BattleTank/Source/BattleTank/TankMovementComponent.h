// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTrackComponet;
class ATank;
/**
 * 
 */
UCLASS()
class BATTLETANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()
	
	
public:
	void BeginPlay() override;
	void IntendMoveForward(float Throw);
private:
	UTrackComponet* LeftTrack;
	UTrackComponet* RightTrack;
	void InitializeTracks();
	ATank* GetTankOnwer();
};
