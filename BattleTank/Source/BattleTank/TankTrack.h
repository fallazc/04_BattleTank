// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * TankTrack is used to set maximum driving force, and to apply forces to the tank
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
		//Sets a Throttle between -1 and +1
		UFUNCTION(BlueprintCallable, Category = Input)
		void SetThrottle(float Throttle);
	
		//Max force per track in Newton
		UPROPERTY(EditDefaultsOnly, Category = Setup)
		float TrackMaxDrivingForce = 40000; // Assume 40 tone, and 1g acceleration
};
