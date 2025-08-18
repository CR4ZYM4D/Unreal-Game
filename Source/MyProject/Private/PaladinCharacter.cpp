// Fill out your copyright notice in the Description page of Project Settings.


#include "PaladinCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
APaladinCharacter::APaladinCharacter(): WalkSpeed(400.f), RunSpeed(600.f), SlowWalkSpeed(200.f)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// create camera boom
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom")); // initialize camera boom
	SpringArmComponent -> SetupAttachment(RootComponent); // attach camera arm to root component i.e player
	SpringArmComponent -> TargetArmLength = 400.f; // set maximum distance of camera boom from player
	SpringArmComponent -> bUsePawnControlRotation = true; // rotate camera arm along with player rotation

	// create camera
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));// initialize the camera
	CameraComponent -> SetupAttachment(SpringArmComponent, USpringArmComponent :: SocketName); // attach to Spring arm socket
	CameraComponent -> bUsePawnControlRotation = false; // dont rotate camera with player rotation

	//setting jump Z velocity and air control

	GetCharacterMovement()->JumpZVelocity = 300.f;
	GetCharacterMovement()->AirControl = 0.5f; // how much movement control player gets midair, 0 none 1 full
	
	
}

// Called when the game starts or when spawned
void APaladinCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{

		// get local player subsystem
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{

			this -> GetCharacterMovement()-> MaxWalkSpeed = WalkSpeed;
			// add input mapping context to player subsystem 
			Subsystem->AddMappingContext(InputMappingContext,  0);
			
		}
		
	}
	
}

// Called every frame
void APaladinCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APaladinCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// binding actions to player

	if (UEnhancedInputComponent* Input = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{

		//looking input action binds
		Input -> BindAction(LookAction, ETriggerEvent::Triggered, this, &APaladinCharacter::Look);

		//movement input action binds
		Input -> BindAction(MoveAction, ETriggerEvent::Triggered, this, &APaladinCharacter::Move);
		Input -> BindAction(JumpAction, ETriggerEvent::Triggered, this, &APaladinCharacter::Jump);
		Input -> BindAction(SprintAction, ETriggerEvent::Started, this, &APaladinCharacter::Run);
		Input -> BindAction(SprintAction, ETriggerEvent::Completed, this, &APaladinCharacter::StopRunning);
		Input -> BindAction(SlowWalkAction, ETriggerEvent::Started, this, &APaladinCharacter::StartSlowWalk);
		Input -> BindAction(SlowWalkAction, ETriggerEvent::Completed, this, &APaladinCharacter::StopSlowWalk);

		// attack input action binds
		Input -> BindAction(LightAttackAction, ETriggerEvent::Triggered, this, &APaladinCharacter::PerformLightAttack);
		Input -> BindAction(HeavyAttackAction, ETriggerEvent::Completed, this, &APaladinCharacter::PerformHeavyAttack);
		Input -> BindAction(SpecialAttackAction, ETriggerEvent::Completed, this, &APaladinCharacter::PerformSpecialAttack);
		

	}
	
}

void APaladinCharacter::Move(const FInputActionValue& InputValue)
{

	//convert input into FVector
	FVector2d InputVector = InputValue.Get<FVector2d>();

	//check if controller is valid for input
	if (IsValid(Controller))
	{
		// get forward direction
		FRotator Rotation = Controller -> GetControlRotation();

		FRotator Yaw = FRotator(0, Rotation.Yaw, 0);

		FVector ForwardDirection = FRotationMatrix(Yaw).GetUnitAxis(EAxis::X);

		FVector RightDirection = FRotationMatrix(Yaw).GetUnitAxis(EAxis::Y);
		
		//add movement input

		AddMovementInput(ForwardDirection, InputVector.Y);

		AddMovementInput(RightDirection, InputVector.X);
	}
	
}

void APaladinCharacter::Look(const FInputActionValue& InputValue)
{

	const FVector2d LookDirection = InputValue.Get<FVector2d>();

	if (IsValid(Controller))
	{

		AddControllerYawInput(LookDirection.X);
		AddControllerPitchInput(LookDirection.Y);
		
	}
	
	
}

void APaladinCharacter::Jump()
{
	Super::Jump();

	//check if character is moving on ground
	if (GetCharacterMovement()-> IsMovingOnGround() )
	{
		//get current forward velocity
		FVector ForwardVelocity = GetVelocity();

		//set its vertical (Z) component 0
		ForwardVelocity.Z = 0.0;

		//get character jump velocity
		const float JumpVelocity = GetCharacterMovement()-> JumpZVelocity;

		// add character jump velocity to current velocity to get launch velocity
		FVector LaunchVelocity = ForwardVelocity + FVector(0.0, 0.0, JumpVelocity);

		//launch character with said launch velocity
		LaunchCharacter(LaunchVelocity, true, true);
		
	}
	
}

void APaladinCharacter::StartSlowWalk()
{
}

void APaladinCharacter::StopSlowWalk()
{
}

void APaladinCharacter::Run()
{

	GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
	
}


void APaladinCharacter::StopRunning()
{

	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	
}

void APaladinCharacter::PerformLightAttack()
{
}

void APaladinCharacter::PerformHeavyAttack()
{
}

void APaladinCharacter::PerformSpecialAttack()
{
}

