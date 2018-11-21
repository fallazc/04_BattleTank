// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	ATank* ControlledTank = GetControlledTank();
	if (ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController possessing: %s"), *(ControlledTank->GetName()));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController not possessing a tank"));
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

// Get world location of linetrace through crosshair, true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	// Find crosshair position
	int32 ViewPortSizeX, ViewportSizeY;
	GetViewportSize(ViewPortSizeX, ViewportSizeY);

	FVector2D ScreenLocation = FVector2D(CrosshairXLocation * ViewPortSizeX, CrosshairYLocation * ViewportSizeY);
	
	// De-project the screen position of the crosshair to a world direction
	// Line-trace along that look direction, and see what we hit(up to max range)
	return true;
}

void ATankPlayerController::AimTowardsCrosshair()
{
	FVector HitLocation;
	if (GetSightRayHitLocation(HitLocation))
	{
		// Get world location if linetrace through crosshair
		// if it hits the landscape
			// Tell controlled tank to aim at this point
		//UE_LOG(LogTemp, Warning, TEXT("Hit location: %s"), *(HitLocation.ToString()));
	}
}