// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Tank.h"




ATankAIController::ATankAIController()
{

}

ATank* ATankAIController::GetPosessedTank()
{
	return (ATank*)GetPawn();
}

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	GetPlayerTank();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetPosessedTank())
	{
		GetPosessedTank()->AimAt(GetPlayerTank()->GetActorLocation());
	}
}

ATank* ATankAIController::GetPlayerTank()
{
	APlayerController* FistPlayerController = GetWorld()->GetFirstPlayerController();
	if (FistPlayerController)
	{
		ATank* tank = (ATank*)FistPlayerController->GetPawn();
		if (tank)
		{
			return tank;
		}
	}
	return nullptr;
}

