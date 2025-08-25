// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MeleeEnemy.h"
#include "MeleeEnemyAnimInstance.generated.h"

/**
 * 
 */

//Declarations

class AMeleeEnemy;

UCLASS()
class MYPROJECT_API UMeleeEnemyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

	public:
		UFUNCTION(BlueprintCallable)
		void UpdateAnimationProperties(float DeltaTime);

	private:
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
		AMeleeEnemy* Enemy;

		//different attributes and properties for different types of animations
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Movement", meta=(AllowPrivateAccess="true"))
		float Speed;

		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Movement", meta=(AllowPrivateAccess="true"))
		float Direction;

	
};
