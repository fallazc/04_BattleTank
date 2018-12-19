// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "Components/InputComponent.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
}

float ATank::GetHealthPercent() const
{
	return CurrentHealth / (float)StartingHealth;
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

float ATank::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	int32 DamagePoints = FPlatformMath::RoundToInt(Damage);
	const int32 DamageToApply = FMath::Clamp<int32>(DamagePoints, 0, CurrentHealth);

	CurrentHealth -= DamageToApply;
	if (CurrentHealth > 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Damage = %f. DamageToApply = %i"), Damage, DamageToApply);
	}
	else
	{
		OnDeath.Broadcast();
	}
	
	return DamageToApply;
}

