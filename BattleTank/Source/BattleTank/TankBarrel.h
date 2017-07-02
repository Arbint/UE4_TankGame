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
	void elevateBarrel(float relativeSpeed);
	void spinBarrel(float relativeSpeed);
	void setBaseTorret(UStaticMeshComponent* BaseTorretToSet);
private:
	UPROPERTY(EditAnywhere, Category = "Setup")
		float maxElevationSpeed = 5.0f;
	UPROPERTY(EditAnywhere, Category = "Setup")
		float maxSpinSpeed = 5.0f;
	UPROPERTY(EditAnywhere, Category = "Setup")
		float maxElevationDegrees = 40;
	UPROPERTY(EditAnywhere, Category = "Setup")
		float minElevationDegrees = -16;
	UPROPERTY(EditAnywhere, Category = "Setup")
		UStaticMeshComponent* BaseTorret;
};
