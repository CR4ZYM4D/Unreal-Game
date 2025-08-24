// Fill out your copyright notice in the Description page of Project Settings.


#include "MeleeEnemyAnimInstance.h"

#include "Kismet/KismetMathLibrary.h"

void UMeleeEnemyAnimInstance::UpdateAnimationProperties(float DeltaTime)
{

	// check if it is null pointer
	if (Enemy == nullptr)
	{
		//cast the enemy pointer for animation
		Enemy = Cast<AMeleeEnemy>(TryGetPawnOwner());
	}

	else
	{

		// get velocity FVector
		FVector Velocity = Enemy->GetVelocity();

		// set its Z component to 0
		Velocity.Z = 0.0f;

		// get speed from velocity FVector
		Speed = Velocity.Size();

		// get aim FRotator
		const FRotator AimRotation = Enemy->GetBaseAimRotation();

		//get movement FRotator from velocity
		const FRotator MovementRotation = UKismetMathLibrary::MakeRotFromX(Velocity);

		// get direction from Aim and Movement Rotators
		Direction = UKismetMathLibrary::NormalizedDeltaRotator(AimRotation, MovementRotation).Yaw;		
	}
	
}
