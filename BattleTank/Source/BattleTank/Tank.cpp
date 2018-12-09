// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankAimingComponent.h"
#include "TankMovementComponent.h"
#include "Projectile.h"
#include "TankBarrel.h"
#include "TankTurret.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//No need to protect pointer as added at construction
	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
	TankMovementComponent = CreateDefaultSubobject<UTankMovementComponent>(FName("Movement Component"));
}

void ATank::setBarrelReference(UTankBarrel* BarrelToSet)
{
	TankAimingComponent->setBarrelReference(BarrelToSet);
	Barrel = BarrelToSet;
}

void ATank::setTurretReference(UTankTurret* TurretToSet)
{
	TankAimingComponent->setTurretReference(TurretToSet);
}

void ATank::Fire()
{
	bool IsReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;
	if (Barrel && IsReloaded)
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

void ATank::AimAt(FVector HitLocation)
{
	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

