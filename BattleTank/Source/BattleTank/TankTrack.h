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
	UTankTrack();

	
	//Sets a Throttle between -1 and +1
	UFUNCTION(BlueprintCallable, Category = Input)
	void SetThrottle(float Throttle);

	void DriveTrack();

protected:
	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	void ApplySidewaysForce();

private:
	float CurrentThrottle = 0;

private:
	UStaticMeshComponent* GetTankRoot() const;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherACtor, UPrimitiveComponent* OtherComponent,
				FVector NormalImpulse, const FHitResult& Hit);

public:
	//Max force per track in Newton
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float TrackMaxDrivingForce = 40000000; // Assume 40 tone, and 1g acceleration
};
