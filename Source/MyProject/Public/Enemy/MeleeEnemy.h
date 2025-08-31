// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "HitInterface.h"
#include "Components/BoxComponent.h"
#include "MeleeEnemy.generated.h"

class UAnimMontage;

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

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
	                         class AController* EventInstigator, AActor* DamageCauser) override;

	virtual void ActivateRightWeapon();
	
	virtual void DeactivateRightWeapon();

private:

	UPROPERTY(BlueprintReadWrite, Category = "Combat",  meta = (AllowPrivateAccess= true))
	float CurrentHealth;
	UPROPERTY(BlueprintReadWrite, Category = "Combat",  meta = (AllowPrivateAccess= true))
	float MaxHealth;
	UPROPERTY(BlueprintReadWrite, Category = "Combat",  meta = (AllowPrivateAccess= true))
	float Damage;

	//Enemy attack montage
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (allowPrivateAccess = true))
	UAnimMontage* AttackMontage;
	
	// enemy weapon hitbox component
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (allowPrivateAccess = true))
	UBoxComponent* WeaponHitbox;
	
	FTimerHandle AttackTimer;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// functions to play random attack montages
	UFUNCTION(BlueprintCallable)
	void MeleeAttack();

	FName GetRandomAttackName(const int32 SectionCount);

	void ResetAttack();

	//function to check weapon hitbox overlap
	UFUNCTION()
	void RightWeaponOverlap(UPrimitiveComponent* OverlappingComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComponent,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);
	
};
