// Fill out your copyright notice in the Description page of Project Settings.
#include "AimingComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "TankBarrel.h"



// Sets default values for this component's properties
UAimingComponent::UAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UAimingComponent::AimingAt(FVector location, float LaunchSpeed)
{
	if (!Barrel)
	{
		UE_LOG(LogTemp, Warning, TEXT("No Firing Point!"));
		return;
	}
	FVector LaunchVelocity{};
	FVector StartLocation = Barrel->GetSocketLocation(FName("FiringPoint"));;
	//calculate the out launch velocity
	//UE_LOG(LogTemp, Warning, TEXT("%s is now aiming form: %s, and aiming at: %s"),*(GetOwner()->GetName()), *(StartLocation.ToString()), *(location.ToString()));
	//TESTED StartLocation, Destination Location are all correct.
	FCollisionResponseParams CollisionResponse{};
	TArray<AActor*> ActorToEgnore{GetOwner()};

	bool bGetProjectileVelocity = UGameplayStatics::SuggestProjectileVelocity(
		this,
		LaunchVelocity,
		StartLocation,
		location,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace,//this is actually important to get a proper answer
		CollisionResponse,
		ActorToEgnore,
		false
		);
	if (bGetProjectileVelocity)
	{
		FVector AimDirection = LaunchVelocity.GetSafeNormal();
		//UE_LOG(LogTemp, Warning, TEXT("%s is looking at: %s"), *(GetOwner()->GetName()), *(AimDirection.ToString()));
		MoveBarrelTowards(AimDirection);
		auto time = GetWorld()->GetTimeSeconds();
		UE_LOG(LogTemp, Warning, TEXT("%f: Barrel Moving at rate: %f"), time, 1.0f);
	}
	else
	{
		auto time = GetWorld()->GetTimeSeconds();
		UE_LOG(LogTemp, Warning, TEXT("%f: Cannot resolve the solution"), time);
		nurtualAiming();
	}
}

// Called when the game starts
void UAimingComponent::BeginPlay()
{
	Super::BeginPlay();
	// ...
}


// Called every frame
void UAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


void UAimingComponent::SetFiringPoint(UTankBarrel* FireingPointToSet)
{
	Barrel = FireingPointToSet;
}

void UAimingComponent::nurtualAiming()
{
	MoveBarrelTowards(GetOwner()->GetActorForwardVector());
}

void UAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	//Work out difference between current barrel rotation and  aimDirection and move the barrel
	FRotator BarrelCurrentRotation = Barrel->GetForwardVector().Rotation();
	FRotator GoalAimingRoation = AimDirection.GetSafeNormal().Rotation();

	FRotator DeltaRotaion = GoalAimingRoation - BarrelCurrentRotation;

	Barrel->elevateBarrel(DeltaRotaion.Pitch);
	Barrel->spinBarrel(DeltaRotaion.Yaw);
}

