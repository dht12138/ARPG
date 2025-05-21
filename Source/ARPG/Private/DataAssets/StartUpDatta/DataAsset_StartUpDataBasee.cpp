// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAssets/StartUpDatta/DataAsset_StartUpDataBasee.h"
#include "AbilitySystem/ArpgAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/ArpgGameplayAbility.h"

void UDataAsset_StartUpDataBasee::GiveToAbilitySystemComponent(UArpgAbilitySystemComponent* InASCToGive,
	int32 ApplyLevel)
{
	check(InASCToGive);

	GrantAbilities(ActivateOnGivenAbilities, InASCToGive, ApplyLevel);
	GrantAbilities(ReactiveAbilities, InASCToGive, ApplyLevel);
}

void UDataAsset_StartUpDataBasee::GrantAbilities(const TArray<TSubclassOf<UArpgGameplayAbility>>& InAbilitiesToGive, 
	UArpgAbilitySystemComponent* InASCToGive, int32 ApplyLevel)
{
	if (InAbilitiesToGive.IsEmpty())
	{
		return;
	}

	for (const TSubclassOf<UArpgGameplayAbility>& Ability : InAbilitiesToGive)
	{
		if (!Ability) continue;

		FGameplayAbilitySpec AbilitySpec(Ability);
		AbilitySpec.SourceObject = InASCToGive->GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;

		//技能被添加到ASC中，添加时根据技能激活策略决定技能激活方式，激活策略在UArpgGameplayAbility类中声明与实现
		InASCToGive->GiveAbility(AbilitySpec);
	}
}
