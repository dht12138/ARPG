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
	/*ȷ�����õ��ࣨUClass����ָ����������ࣨ�� TSubclassOf<AActor> ֻ�ܴ洢 AActor ����������������ã���*/

	UPROPERTY(EditDefaultsOnly, Category = "StartUpData")
	TArray<TSubclassOf<UArpgGameplayAbility>> ReactiveAbilities;

	void GrantAbilities(const TArray<TSubclassOf<UArpgGameplayAbility>>& InAbilitiesToGive,
		UArpgAbilitySystemComponent* InASCToGive, int32 ApplyLevel = 1);
};
