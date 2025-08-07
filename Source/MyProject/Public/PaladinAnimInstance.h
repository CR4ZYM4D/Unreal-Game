// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PaladinAnimInstance.generated.h"

// Declaring character class here
class APaladinCharacter;

/**
 * 
 */
UCLASS()
class MYPROJECT_API UPaladinAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

	public:

		UFUNCTION(BlueprintCallable)
		 void UpdateAnimationProperties(float deltatime);

		virtual void NativeInitializeAnimation() override;

	private:

	//setting character pointer
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Movement", meta=(AllowPrivateAccess="true"))
	APaladinCharacter* PaladinCharacter;

	//different attributes and properties for different types of animations
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Movement", meta=(AllowPrivateAccess="true"))
	float Speed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Movement", meta=(AllowPrivateAccess="true"))
	float Direction;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Movement", meta=(AllowPrivateAccess="true"))
	bool IsInAir;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Movement", meta=(AllowPrivateAccess="true"))
	bool IsBlocking;
	
};
