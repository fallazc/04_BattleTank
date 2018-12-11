// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	ATank* ControlledTank = Cast<ATank>(GetPawn());
	ATank* PlayerPawn = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (PlayerPawn)
	{
		// TODO check radius is in cm
		MoveToActor(PlayerPawn, AcceptanceRadius);
		ControlledTank->AimAt(PlayerPawn->GetActorLocation());
		ControlledTank->Fire();
	}
}
