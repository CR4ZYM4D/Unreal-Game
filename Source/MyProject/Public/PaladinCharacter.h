// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "InputActionValue.h"

#include "PaladinCharacter.generated.h"



//declaration
class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;

UCLASS()
class MYPROJECT_API APaladinCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APaladinCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "EnhancedInputType") // values can be changed in engine also
	UInputMappingContext* InputMappingContext;

	UPROPERTY(EditAnywhere, Category = "EnhancedInputType")
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, Category = "EnhancedInputType")
	UInputAction* LookAction;
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//declaring the move function to handle movement inputs
	void Move(const FInputActionValue& InputValue);

	void Look(const FInputActionValue& InputValue);
	
private:

	//declare spring arm component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = true))
	USpringArmComponent* SpringArmComponent;

	//declare camera component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = true))
	UCameraComponent* CameraComponent;
	
};
