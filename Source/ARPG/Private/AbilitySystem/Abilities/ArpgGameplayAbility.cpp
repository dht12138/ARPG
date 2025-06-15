// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/ArpgGameplayAbility.h"
#include "AbilitySystem/ArpgAbilitySystemComponent.h"
#include "Components/Combat/PawnCombatComponent.h"

void UArpgGameplayAbility::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, 
	const FGameplayAbilitySpec& Spec)
{
	Super::OnGiveAbility(ActorInfo, Spec);
	
	if (ActorInfo && !Spec.IsActive())
	{
		ActorInfo->AbilitySystemComponent->TryActivateAbility(Spec.Handle);
	}
	/*���������������ܱ��������ɫʱ�������������������������Լ���ܣ�
		��ɫ��Ϣ��Ч��ActorInfo �ǿգ���
		���ܵ�ǰδ���!Spec.IsActive()����*/

}

void UArpgGameplayAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, 
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, 
	bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	if (AbilityActivationPolicy == EArpgAbilityActivationPolicy::OnGiven)
	{
		if (ActorInfo)
		{
			ActorInfo->AbilitySystemComponent->ClearAbility(Handle);
		}
	}
}

UPawnCombatComponent* UArpgGameplayAbility::GetPawnCombatCompFromActorInfo() const
{
	return GetAvatarActorFromActorInfo()->FindComponentByClass<UPawnCombatComponent>();

}

UArpgAbilitySystemComponent* UArpgGameplayAbility::GetArpgAbilitySystemCompFromActorInfo() const
{
	return Cast<UArpgAbilitySystemComponent>(CurrentActorInfo->AbilitySystemComponent);
}
