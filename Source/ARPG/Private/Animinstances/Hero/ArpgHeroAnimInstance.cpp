// Fill out your copyright notice in the Description page of Project Settings.


#include "Animinstances/Hero/ArpgHeroAnimInstance.h"
#include "Characters/ARPGHeroCharacter.h"

void UArpgHeroAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	if (OwningChar)
	{
		OwningHeroChar = Cast<AARPGHeroCharacter>(OwningChar);
	}
}

void UArpgHeroAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);

	if (bHasAcceleration)
	{
		IdleElpasedTime = 0.f;
		bShouldEnterRelaxState = false;
	}
	else
	{
		IdleElpasedTime += DeltaSeconds;

		bShouldEnterRelaxState = (IdleElpasedTime >= EnterRelaxStateThreShold);
	}
}
