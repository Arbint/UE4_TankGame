// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	void elevateBarrel(float RelativeSpeed);
private:
	UPROPERTY(EditAnywhere, Category = "Setup")
		float maxElevationSpeed = 20.0f;
	UPROPERTY(EditAnywhere, Category = "Setup")
		float maxElevationDegrees = 40;
	UPROPERTY(EditAnywhere, Category = "Setup")
		float minElevationDegrees = -16;
};
