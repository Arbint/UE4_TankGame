// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Tank.generated.h"

class UAimingComponent;
class UTankBarrel;
class AProjectile;
class UTrackComponet;
class UTankMovementComponent;
UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	//Functionality Component
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Functionality")
		UAimingComponent* AimingComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Functionality")
		UTankMovementComponent* MovementComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
		float LaunchingSpeed = 100000.0f;
public:	

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visual")
		UStaticMeshComponent* TankBase;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visual")
		UTrackComponet* LeftTankTrack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visual")
		UTrackComponet* RightTankTrack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visual")
		UStaticMeshComponent* TankTorret;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visual")
		UTankBarrel* Barrel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visual")
		FName TorretSocketName = NAME_None;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visual")
		FName BarrelSocketName = NAME_None;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerEye")
		USpringArmComponent* CameraBoom;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerEye")
		USceneComponent* CameraBoomAzimuthGimbal;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerEye")
		UCameraComponent* PlayerEye;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerEye")
		float TankAimingSensitiviy = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
		TSubclassOf<AProjectile> ProjectTileToFire;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
		float ProjectileLodingTime = 3;

	


public:
	void LookUp(float amount);
	void LookRight(float amount);
	void AimAt(FVector location);
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void SetupFirePointToAimComp(UTankBarrel* FiringPointToSet);
	void NurtualAim();
	void Fire();
	void SetTrackthrottle(UTrackComponet* tracToSet, float amount);
	void MoveForward(float amount);
private:
	float LastFireTime;
};
