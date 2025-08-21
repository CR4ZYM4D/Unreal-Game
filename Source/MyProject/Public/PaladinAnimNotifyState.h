// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "PaladinCharacter.h"
#include "PaladinAnimNotifyState.generated.h"


/**
 * 
 */

//declarations
class APaladinCharacter;

UCLASS()
class MYPROJECT_API UPaladinAnimNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()

	public:

	UPROPERTY()
	APaladinCharacter* PlayerCharacter;

	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;

	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
	
};
