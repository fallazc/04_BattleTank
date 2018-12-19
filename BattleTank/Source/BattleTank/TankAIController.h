// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"



/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	

private:
	virtual void BeginPlay() override;

	virtual void SetPawn(APawn* Pawn) override;

	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnPossesedTankDeath();

	//How close can the AI Tank get
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float AcceptanceRadius = 8000.f;
};
