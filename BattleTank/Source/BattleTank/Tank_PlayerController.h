// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Tank_PlayerController.generated.h"

class ATank;
/**
 * 
 */
UCLASS()
class BATTLETANK_API ATank_PlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ATank_PlayerController();
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	void LookUp(float amount);
	void LookRight(float amount);
	ATank* GetControlledTank();
	virtual void Tick(float DeltaSeconds) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	float crossHairXLocation = 0.5f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	float crossHairYLocation = 0.33333f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	float sightReach = 1000000;

private:
	ATank* TankPossessed;
	void QuitGame();
	void AimAtCrossHair();
	bool GetCrossHairLookDirection(FVector2D ScreeLocation, FVector& LookDirection);
	bool LineTraceThroughCrosshair(FHitResult &outHit);
	FVector2D GetCrossHairScreenLocation();
};
