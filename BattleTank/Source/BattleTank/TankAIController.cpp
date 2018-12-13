// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	APawn* ControlledPawn = GetPawn();
	APawn* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (ensure(ControlledPawn))
	{
		if (ensure(PlayerPawn))
		{
			// TODO check radius is in cm
			MoveToActor(PlayerPawn, AcceptanceRadius);
			UTankAimingComponent* AimingComponent = ControlledPawn->FindComponentByClass<UTankAimingComponent>();
			AimingComponent->AimAt(PlayerPawn->GetActorLocation());
			//ControlledPawn->Fire();
		}
	}
}
