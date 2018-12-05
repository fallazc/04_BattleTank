// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

// Forward declaration
class UTankBarrel;
class UTankTurret;

// Holds barrel's properties and Elevate method
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	void setBarrelReference(UTankBarrel* BarrelToSet);

	void setTurretReference(UTankTurret* BarrelToSet);

	void AimAt(FVector HitLocation, float LauncSpeed);

private:
	UTankBarrel* Barrel = nullptr;

	UTankTurret* Turret = nullptr;
	
	void MoveBarrelTowards(FVector AimDirection);
};
