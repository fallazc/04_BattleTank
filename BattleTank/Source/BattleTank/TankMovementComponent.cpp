// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialize(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	/*FString TankName = GetOwner()->GetName();
	FString AIForwardIntentionString = MoveVelocity.ToCompactString();

	//No need to call super as we are replacing the functionality
	UE_LOG(LogTemp, Warning, TEXT("%s vectoring to %s"), *TankName, *AIForwardIntentionString);*/
	FVector AIForwardIntention = MoveVelocity.GetSafeNormal();
	FVector TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();

	float ForwardThrow = FVector::DotProduct(AIForwardIntention, TankForward);
	IntendMove(ForwardThrow);
}

void UTankMovementComponent::IntendMove(float Throw)
{
	if (LeftTrack && RightTrack)
	{
		LeftTrack->SetThrottle(Throw);
		RightTrack->SetThrottle(Throw);
	}
}


void UTankMovementComponent::IntendTurn(float Throw)
{
	if (LeftTrack && RightTrack)
	{
		
		LeftTrack->SetThrottle(Throw);
		RightTrack->SetThrottle(-Throw);
	}
}
