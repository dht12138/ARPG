// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DataAsset_StartUpDataBasee.generated.h"

class UArpgGameplayAbility;
class UArpgAbilitySystemComponent;

/**
 * 
 */
UCLASS()
class ARPG_API UDataAsset_StartUpDataBasee : public UDataAsset
{
	GENERATED_BODY()
	
public:
	virtual void GiveToAbilitySystemComponent(UArpgAbilitySystemComponent* InASCToGive, int32 ApplyLevel = 1);

protected:
	UPROPERTY(EditDefaultsOnly, Category = "StartUpData")
	TArray<TSubclassOf<UArpgGameplayAbility>> ActivateOnGivenAbilities;
	/*确保引用的类（UClass）是指定基类的子类（如 TSubclassOf<AActor> 只能存储 AActor 或其派生类的类引用）。*/

	UPROPERTY(EditDefaultsOnly, Category = "StartUpData")
	TArray<TSubclassOf<UArpgGameplayAbility>> ReactiveAbilities;

	void GrantAbilities(const TArray<TSubclassOf<UArpgGameplayAbility>>& InAbilitiesToGive,
		UArpgAbilitySystemComponent* InASCToGive, int32 ApplyLevel = 1);
};
