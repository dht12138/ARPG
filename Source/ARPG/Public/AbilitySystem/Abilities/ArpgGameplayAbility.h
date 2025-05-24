// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "ArpgGameplayAbility.generated.h"

class UPawnCombatComponent;

UENUM(BlueprintType)
enum class EArpgAbilityActivationPolicy : uint8
{
	OnTriggered,
	OnGiven
};
/**
 * 
 */
UCLASS()
class ARPG_API UArpgGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
	
protected:
	//~ Begin UGameplayAbility Interface.
	virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, 
		const FGameplayAbilitySpec& Spec) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, 
		const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, 
		bool bReplicateEndAbility, bool bWasCancelled) override;
	//~ End UGameplayAbility Interface

	UPROPERTY(EditDefaultsOnly, Category = "Arpg|Ability")
	EArpgAbilityActivationPolicy AbilityActivationPolicy = EArpgAbilityActivationPolicy::OnTriggered;

	UFUNCTION(BlueprintPure, Category = "Arpg|Ability")
	UPawnCombatComponent* GetPawnCombatCompFromActorInfo() const;
};
