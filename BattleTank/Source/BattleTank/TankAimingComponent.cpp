// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Projectile.h"
#include "Engine/World.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Kismet/GameplayStatics.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if (ensure(Barrel))
	{
		FVector LaunchVelocity(0);
		FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

		//Calculate the out launch velocity
		bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
			this, 
			LaunchVelocity,
			StartLocation, 
			HitLocation, 
			LaunchSpeed,
			false,
			0,
			0,
			ESuggestProjVelocityTraceOption::DoNotTrace
		);

		if (bHaveAimSolution)
		{
			FVector AimDirection = LaunchVelocity.GetSafeNormal();
			MoveBarrelTowards(AimDirection);
		}
	}
}

void UTankAimingComponent::Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	if (ensure(BarrelToSet && TurretToSet))
	{
		Barrel = BarrelToSet;
		Turret = TurretToSet;
	}
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	// Work-out difference between current barrel rotation and Aimdirection
	FRotator BarrelRotator = Barrel->GetForwardVector().Rotation();
	FRotator AimAsRotator = AimDirection.Rotation();
	FRotator DeltaRotator = AimAsRotator - BarrelRotator;

	Barrel->Elevate(DeltaRotator.Pitch);
	Turret->Rotate(DeltaRotator.Yaw);
}

void UTankAimingComponent::BeginPlay()
{
	//So that first fire is after initial reload
	Super::BeginPlay();
	LastFireTime = FPlatformTime::Seconds();
}

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	if ((FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds)
	{
		FiringState = EFiringState::Reloading;
	}
	//TODO handle aiming and locked states
}

void UTankAimingComponent::Fire()
{
	if (EFiringState::Aiming == FiringState)
	{
		if (ensure(Barrel) && ensure(BlueprintProjectile))
		{
			FName SocketName("Projectile");
			FVector Location = Barrel->GetSocketLocation(SocketName);
			FRotator Rotation = Barrel->GetSocketRotation(SocketName);
			//Spawn a projectile at the socket location of the barrel
			AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(BlueprintProjectile, Location, Rotation);
			Projectile->LauchnProjectile(LaunchSpeed);

			LastFireTime = FPlatformTime::Seconds();
		}
	}
}
