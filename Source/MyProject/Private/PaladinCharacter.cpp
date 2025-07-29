// Fill out your copyright notice in the Description page of Project Settings.


#include "PaladinCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

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

}

