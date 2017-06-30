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
private:
	ATank* TankPossessed;
	void QuitGame();
};
