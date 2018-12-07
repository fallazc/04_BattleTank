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
	APawn* PlayerPawn = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (PlayerPawn)
	{
		ControlledTank->AimAt(PlayerPawn->GetActorLocation());
		ControlledTank->Fire();
	}
}
