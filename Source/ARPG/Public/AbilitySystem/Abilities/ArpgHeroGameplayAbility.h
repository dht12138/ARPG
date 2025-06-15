// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/ArpgGameplayAbility.h"
#include "ArpgHeroGameplayAbility.generated.h"

class AARPGHeroCharacter;
class AARPGHeroController;

/**
 * 
 */
UCLASS()
class ARPG_API UArpgHeroGameplayAbility : public UArpgGameplayAbility
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure, Category = "Arpg|Ability")
	AARPGHeroCharacter* GetHeroCharFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "Arpg|Ability")
	AARPGHeroController* GetHeroConFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "Arpg|Ability")
	UHeroCombatComponent* GetHeroCombatCompFromActorInfo();

private:
	TWeakObjectPtr<AARPGHeroCharacter> CachedHeroChar;
	TWeakObjectPtr<AARPGHeroController> CachedHeroCon;
	//只保存对象引用，不增加引用计数
};
