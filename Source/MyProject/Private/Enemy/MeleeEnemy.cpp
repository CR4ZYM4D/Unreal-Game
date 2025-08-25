// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/MeleeEnemy.h"


// Sets default values
AMeleeEnemy::AMeleeEnemy()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMeleeEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMeleeEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMeleeEnemy::HitInterface_Implementation(const FHitResult& SweepResult)
{
	IHitInterface::HitInterface_Implementation(SweepResult);
}

float AMeleeEnemy::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
	class AController* EventInstigator, AActor* DamageCauser)
{

	if (CurrentHealth - DamageAmount <= 0.f)
	{
		CurrentHealth = 0.f;
		//call death montage animation function from BP
	}

	else
	{
		CurrentHealth -= DamageAmount;
	}
	return DamageAmount;
}


