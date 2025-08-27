// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "HitInterface.h"
#include "MeleeEnemy.generated.h"

UCLASS()
class MYPROJECT_API AMeleeEnemy : public ACharacter, public IHitInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMeleeEnemy();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//override HitInterface implementation
	virtual void HitInterface_Implementation(const FHitResult& SweepResult) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

private:

	UPROPERTY(BlueprintReadWrite, Category = "Combat",  meta = (AllowPrivateAccess= true))
	float CurrentHealth;
	UPROPERTY(BlueprintReadWrite, Category = "Combat",  meta = (AllowPrivateAccess= true))
	float MaxHealth;
	UPROPERTY(BlueprintReadWrite, Category = "Combat",  meta = (AllowPrivateAccess= true))
	float Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (allowPrivateAccess = true))
	UAnimMontage* AttackMontage;

	FTimerHandle AttackTimer;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void MeleeAttack();

	FName GetAttackName(const int32 SectionCount);

	void ResetAttack();

};
