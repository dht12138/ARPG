// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAssets/StartUpDatta/DataAsset_HeroStartUpData.h"
#include "AbilitySystem/Abilities/ArpgGameplayAbility.h"
#include "AbilitySystem/ArpgAbilitySystemComponent.h"

bool FArpgHeroAbilitySet::IsValid() const
{
    return InputTag.IsValid() && AbilityToGrant;
}

void UDataAsset_HeroStartUpData::GiveToAbilitySystemComponent(UArpgAbilitySystemComponent* InASCToGive,
    int32 ApplyLevel)
{
    Super::GiveToAbilitySystemComponent(InASCToGive, ApplyLevel);

    for (const FArpgHeroAbilitySet& AbililtySet : HeroStartUpAbilitySet)
    {
        if (!AbililtySet.IsValid()) continue;

        FGameplayAbilitySpec AbilitySpec(AbililtySet.AbilityToGrant);
        AbilitySpec.SourceObject = InASCToGive->GetAvatarActor();
        AbilitySpec.Level = ApplyLevel;
        AbilitySpec.DynamicAbilityTags.AddTag(AbililtySet.InputTag);
        //ʹ��DynamicAbilityTags ��GameplayAbilityʹ��InputTag���б�ǣ�����ʹ�ø�InputTag������GameplayAbility

        InASCToGive->GiveAbility(AbilitySpec);
    }

}
