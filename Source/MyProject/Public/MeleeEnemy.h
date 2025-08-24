// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MeleeEnemy.generated.h"

UCLASS()
class MYPROJECT_API AMeleeEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMeleeEnemy();

	// Called every frame
	virtual void Tick(float DeltaTime) override;



private:

	UPROPERTY(BlueprintReadWrite, Category = "Combat",  meta = (AllowPrivateAccess= true))
	float CurrentHealth;
	UPROPERTY(BlueprintReadWrite, Category = "Combat",  meta = (AllowPrivateAccess= true))
	float MaxHealth;
	UPROPERTY(BlueprintReadWrite, Category = "Combat",  meta = (AllowPrivateAccess= true))
	float Damage;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


};
