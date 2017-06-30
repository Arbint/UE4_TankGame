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

ATank* ATankAIController::GetPlayerTank()
{
	APlayerController* FistPlayerController = GetWorld()->GetFirstPlayerController();
	if (FistPlayerController)
	{
		ATank* tank = (ATank*)FistPlayerController->GetPawn();
		if (tank)
		{
			UE_LOG(LogTemp, Warning, TEXT("Find Player's tank: %s"), *(tank->GetName()));
			return tank;
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("Cannot find player's tank"));
	return nullptr;
}

