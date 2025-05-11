// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animinstances/ArpgCharacterAnimInstance.h"
#include "ArpgHeroAnimInstance.generated.h"

class AARPGHeroCharacter;

/**
 * 
 */
UCLASS()
class ARPG_API UArpgHeroAnimInstance : public UArpgCharacterAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimData|Refrences")
	AARPGHeroCharacter* OwningHeroChar;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimData|LocomotionData")
	bool bShouldEnterRelaxState;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AnimData|LocomotionData")
	float EnterRelaxStateThreShold = 10.f;

	float IdleElpasedTime;
};
