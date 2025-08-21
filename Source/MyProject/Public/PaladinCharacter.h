// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "Components/BoxComponent.h"
#include "PaladinCharacter.generated.h"



//declaration
class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
class UAnimMontage;

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
	
	// Input Actions Declarations

	// movement and looking actions
	UPROPERTY(EditAnywhere, Category = "EnhancedInputType")
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, Category = "EnhancedInputType")
	UInputAction* LookAction;

	//jumping actions
	UPROPERTY(EditAnywhere, Category = "EnhancedInputType")
	UInputAction* JumpAction;

	//sprinting action
	UPROPERTY(EditAnywhere, Category = "EnhancedInputType")
	UInputAction* SprintAction;

	//slow walking action
	UPROPERTY(EditAnywhere, Category = "EnhancedInputType")
	UInputAction* SlowWalkAction;

	//attack actions

	//light attack action
	UPROPERTY(EditAnywhere, Category = "Combat")
	UInputAction* LightAttackAction;

	//heavy attack action
	UPROPERTY(EditAnywhere, Category = "Combat")
	UInputAction* HeavyAttackAction;

	//special attack action
	UPROPERTY(EditAnywhere, Category = "Combat")
	UInputAction* SpecialAttackAction;
	
	//default walk speed
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Movement")
	float WalkSpeed;

	//running speed
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Movement")
	float RunSpeed;

	//slow walking speed
	UPROPERTY(VisibleAnywhere, BluePrintReadWrite, Category = "Movement")
	float SlowWalkSpeed;

	// function to play the anim montage
	virtual void PlayMontage(class UAnimMontage* AnimMontage, float PlayRate = 1, FName SectionName = NAME_None);;

	//function to check if weapon overlaps with something
	UFUNCTION()
	void RightWeaponOverlap(UPrimitiveComponent* OverlappingComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComponent,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//declaring the move function to handle movement inputs
	void Move(const FInputActionValue& InputValue);

	// look function to move camera around
	void Look(const FInputActionValue& InputValue);

	// take a wild fucking guess what these are for
	void Jump();

	virtual void StartSlowWalk();

	virtual void StopSlowWalk();

	virtual void Run();

	virtual void StopRunning();

	virtual void PerformLightAttack();

	virtual void PerformHeavyAttack();

	virtual void PerformSpecialAttack();

	virtual void DeactivateRightWeapon();
	
	virtual void ActivateRightWeapon();

private:

	//declare spring arm component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = true))
	USpringArmComponent* SpringArmComponent;

	//declare camera component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = true))
	UCameraComponent* CameraComponent;

	//Attack Anim Montage class
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Montage", meta = (AllowPrivateAccess = "true"))
	UAnimMontage* AttackMontage;

	//Right Weapon Hitbox component
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Combat", meta = (AllowPrivateAccess = "true"))
	UBoxComponent* RightWeaponBox;
	
};
