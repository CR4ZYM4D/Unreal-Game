// Fill out your copyright notice in the Description page of Project Settings.


#include "PaladinAnimInstance.h"

#include "PaladinCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UPaladinAnimInstance::UpdateAnimationProperties(float deltatime)
{

	//check if character pointer is null
	if (PaladinCharacter == nullptr)
	{
		// cast it same as in NativeInitializeAnimation
		PaladinCharacter = Cast<APaladinCharacter>(TryGetPawnOwner());
	}
	else
	{
		// get velocity FVector
		FVector Velocity = PaladinCharacter->GetVelocity();

		// set its Z component to 0
		Velocity.Z = 0.0f;

		// get speed from velocity FVector
		Speed = Velocity.Size();

		//check if character is in air by checking if he is falling
		IsInAir = PaladinCharacter->GetCharacterMovement()->IsFalling();

		// get aim FRotator
		const FRotator AimRotation = PaladinCharacter->GetBaseAimRotation();

		//get movement FRotator from velocity
		const FRotator MovementRotation = UKismetMathLibrary::MakeRotFromX(Velocity);

		// get direction from Aim and Movement Rotators
		Direction = UKismetMathLibrary::NormalizedDeltaRotator(AimRotation, MovementRotation).Yaw;
		
	}
}

void UPaladinAnimInstance::NativeInitializeAnimation()
{

	//set character pointer to player

	PaladinCharacter = Cast<APaladinCharacter>(TryGetPawnOwner());

	
	
}
