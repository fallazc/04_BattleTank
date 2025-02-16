// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankAimingComponent.h"
#include "Tank.h" // So we can implement OnDeath
#include "Engine/World.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::SetPawn(APawn* Pawn)
{
	Super::SetPawn(Pawn);

	ATank* PossessedTank = Cast<ATank>(Pawn);
	if (PossessedTank)
	{
		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPossesedTankDeath);
	}
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	APawn* ControlledPawn = GetPawn();
	APawn* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (ControlledPawn)
	{
		if (PlayerPawn)
		{
			// TODO check radius is in cm
			MoveToActor(PlayerPawn, AcceptanceRadius);
			UTankAimingComponent* AimingComponent = ControlledPawn->FindComponentByClass<UTankAimingComponent>();
			AimingComponent->AimAt(PlayerPawn->GetActorLocation());
			AimingComponent->Fire();
		}
	}
}

void ATankAIController::OnPossesedTankDeath()
{
	APawn* PossessedPawn = GetPawn();
	if (PossessedPawn)
	{
		PossessedPawn->DetachFromControllerPendingDestroy();
	}
}
