// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataAssets/StartUpDatta/DataAsset_StartUpDataBasee.h"
#include "GameplayTagContainer.h"
#include "DataAsset_HeroStartUpData.generated.h"

USTRUCT(BlueprintType)
struct FArpgHeroAbilitySet
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (Categories = "InputTag"))
	FGameplayTag InputTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UArpgGameplayAbility> AbilityToGrant;

	bool IsValid() const;

};

/**
 * 
 */
UCLASS()
class ARPG_API UDataAsset_HeroStartUpData : public UDataAsset_StartUpDataBasee
{
	GENERATED_BODY()  
	
public:
	virtual void GiveToAbilitySystemComponent(UArpgAbilitySystemComponent* InASCToGive, 
		int32 ApplyLevel = 1) override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "StartUpData", meta = (TitleProperty = "InputTag"))
	TArray<FArpgHeroAbilitySet> HeroStartUpAbilitySet;
};
