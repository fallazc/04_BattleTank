// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	FTankDelegate OnDeath;

protected:
	// Called to bind functionality to input
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditDefaultsOnly, category = Setup)
	int32 StartingHealth = 100;

	UPROPERTY(VisibleAnywhere, category = Health)
	int32 CurrentHealth;

public:	
	//Returns current health as a percentage of starting health between 0 and 1
	UFUNCTION(BlueprintPure, Category = Health)
	float GetHealthPercent() const;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
};
