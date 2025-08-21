// Fill out your copyright notice in the Description page of Project Settings.


#include "PaladinAnimNotifyState.h"

void UPaladinAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float TotalDuration, const FAnimNotifyEventReference& EventReference)
{

	//get mesh component owner if not nullptr
	if (MeshComp != nullptr && MeshComp->GetOwner())
	{
		PlayerCharacter = Cast<APaladinCharacter>(MeshComp->GetOwner());

		//call ActivateRightWeapon fn if not nullptr

		if (PlayerCharacter != nullptr)
		{

			PlayerCharacter -> ActivateRightWeapon();
			
		}
		
	}
	
}

void UPaladinAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                        const FAnimNotifyEventReference& EventReference)
{

	//get mesh component owner if not nullptr
	if (MeshComp != nullptr && MeshComp->GetOwner())
	{
		//no need to cast because if mesh comp not null then player pointer is already set
		//call DeactivateRightWeapon fn if not nullptr

		if (PlayerCharacter != nullptr)
		{

			PlayerCharacter -> DeactivateRightWeapon();
			
		}
		
	}
	
}
