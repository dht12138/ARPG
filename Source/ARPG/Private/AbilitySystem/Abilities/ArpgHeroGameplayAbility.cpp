// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/ArpgHeroGameplayAbility.h"
#include "Characters/ARPGHeroCharacter.h"
#include "Controllers/ARPGHeroController.h"

AARPGHeroCharacter* UArpgHeroGameplayAbility::GetHeroCharFromActorInfo()
{
    if (!CachedHeroChar.IsValid())
    {
        CachedHeroChar = Cast<AARPGHeroCharacter>(CurrentActorInfo->AvatarActor);
    }

    return CachedHeroChar.IsValid() ? CachedHeroChar.Get() : nullptr;
    //CachedHeroChar.Get() Ω‚“˝”√
}

AARPGHeroController* UArpgHeroGameplayAbility::GetHeroConFromActorInfo()
{
    if (CachedHeroCon.IsValid())
    {
        CachedHeroCon = Cast<AARPGHeroController>(CurrentActorInfo->PlayerController);
    }

    return CachedHeroCon.IsValid() ? CachedHeroCon.Get() : nullptr;
}

UHeroCombatComponent* UArpgHeroGameplayAbility::GetHeroCombatCompFromActorInfo()
{
    return GetHeroCharFromActorInfo()->GetHeroCombatComponent();
}
