// Fill out your copyright notice in the Description page of Project Settings.


#include "PaladinCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

// Sets default values
APaladinCharacter::APaladinCharacter()
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

		Input -> BindAction(MoveAction, ETriggerEvent::Triggered, this, &APaladinCharacter::Move);
		Input -> BindAction(LookAction, ETriggerEvent::Triggered, this, &APaladinCharacter::Look);
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

