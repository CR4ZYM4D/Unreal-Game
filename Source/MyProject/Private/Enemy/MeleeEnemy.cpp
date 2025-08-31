// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/MeleeEnemy.h"

#include "PaladinCharacter.h"
#include "Enemy/MeleeEnemyAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"


// Sets default values
AMeleeEnemy::AMeleeEnemy(): CurrentHealth(100.f), MaxHealth(100.f), Damage(40.f)
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WeaponHitbox = CreateDefaultSubobject<UBoxComponent>(TEXT("WeaponHitbox"));
	WeaponHitbox -> SetupAttachment(GetMesh(),FName("SwordSocket"));
}

// Called when the game starts or when spawned
void AMeleeEnemy::BeginPlay()
{
	Super::BeginPlay();

	 // SetActorEnableCollision(false);
	this -> GetCharacterMovement()-> MaxWalkSpeed = 200.f;

	// binding function for right weapon overlap
	WeaponHitbox -> OnComponentBeginOverlap.AddDynamic(this, &AMeleeEnemy::RightWeaponOverlap);

	//setting up right weapon collision
	WeaponHitbox -> SetCollisionEnabled(ECollisionEnabled::NoCollision);
	WeaponHitbox -> SetCollisionObjectType(ECollisionChannel:: ECC_WorldDynamic);
	WeaponHitbox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	WeaponHitbox->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse:: ECR_Overlap);
	
}

void AMeleeEnemy::MeleeAttack()
{
		
	// get current anim instance
	UMeleeEnemyAnimInstance* CurrentInstance =  Cast<UMeleeEnemyAnimInstance>(GetMesh()->GetAnimInstance());

	//check neither attack montage and current anim instance are null pointers
	if (CurrentInstance && AttackMontage)
	{

		//get number of sections in attack montage
		const int32 SectionCount = AttackMontage->CompositeSections.Num();

		//get the name of a random section in the montage
		const FName SectionName = GetRandomAttackName(SectionCount);
		
		//get the section index
		const int32 SectionIndex = AttackMontage->GetSectionIndex(SectionName);

		//get length of section
		const float SectionLength = AttackMontage->GetSectionLength(SectionIndex);
		
		CurrentInstance->Montage_Play(AttackMontage);

		//play the selected random section in montage
		CurrentInstance-> Montage_JumpToSection(SectionName, AttackMontage);

		GetWorldTimerManager().SetTimer(AttackTimer, this, &AMeleeEnemy::ResetAttack, SectionLength, false);
	}	
	
}

FName AMeleeEnemy::GetRandomAttackName(const int32 SectionCount)
{
	switch (const int32 Section {FMath :: RandRange(1, SectionCount)})
	{
		case 0: return FName("LightAttack");
		
		case 1: return FName("HeavyAttack");
		
		default: return FName("LightAttack");
	}
	
}

void AMeleeEnemy::ResetAttack()
{
}

void AMeleeEnemy::RightWeaponOverlap(UPrimitiveComponent* OverlappingComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	//check if sweep hit something
	if (IsValid(SweepResult.GetActor()) && SweepResult.GetActor() != this)
	{
		if (OtherActor)
		{
			APaladinCharacter* Player = Cast<APaladinCharacter>(OtherActor);
			if (Player)
			{
				
			}
		}
	}
	
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

void AMeleeEnemy::DeactivateRightWeapon()
{

	WeaponHitbox -> SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
}

void AMeleeEnemy::ActivateRightWeapon()
{

	WeaponHitbox -> SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	
}

