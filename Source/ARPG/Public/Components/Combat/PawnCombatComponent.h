// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/PawnExtensionComponentBase.h"
#include "GameplayTagContainer.h"
#include "PawnCombatComponent.generated.h"

class AArpgWeaponBase;
/**
 * 
 */
UCLASS()
class ARPG_API UPawnCombatComponent : public UPawnExtensionComponentBase
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Arpg|Combat")
	void RegisterSpawnedWeapon(FGameplayTag InWeaponTagToRegister, AArpgWeaponBase* InWeaponToRegister,
		bool bRegisterAsEquippedWeapon = false);

	UFUNCTION(BlueprintCallable, Category = "Arpg|Combat")
	AArpgWeaponBase* GetCharacterCarriedWeaponByTag(FGameplayTag InWeaponTagToGet) const;

	UPROPERTY(BlueprintReadWrite, Category = "Arpg|Combat")
	FGameplayTag CurrentEquippedWeaponTag;

	UFUNCTION(BlueprintCallable, Category = "Arpg|Combat")
	AArpgWeaponBase* GetCharacterCurrentEquippedWeapon() const;

private:
	TMap<FGameplayTag, AArpgWeaponBase*> CharacterCarriedWeaponMap;
};
