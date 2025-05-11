// Fill out your copyright notice in the Description page of Project Settings.


#include "Animinstances/ArpgCharacterAnimInstance.h"
#include "Characters/ARPGBaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"


void UArpgCharacterAnimInstance::NativeInitializeAnimation()
{
	OwningChar = Cast<AARPGBaseCharacter>(TryGetPawnOwner());

	if (OwningChar)
	{
		OwningMovementComp = OwningChar->GetCharacterMovement();
	}
}

void UArpgCharacterAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	if (!OwningChar || !OwningMovementComp)
	{ 
		return;
	}

	GroundSpeed = OwningChar->GetVelocity().Size2D();

	bHasAcceleration = OwningMovementComp->GetCurrentAcceleration().SizeSquared2D() > 0.f;
}
