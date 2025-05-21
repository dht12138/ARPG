// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "ARPGBaseCharacter.generated.h"

class UArpgAbilitySystemComponent;
class UArpgAttributeSet;
class UDataAsset_StartUpDataBasee;

UCLASS()
class ARPG_API AARPGBaseCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AARPGBaseCharacter();

	//~ Begin IAbilitySystemInterface Interface.
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	//~ End IAbilitySystemInterface Interface

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	UArpgAbilitySystemComponent* ArpgAbilitySystemComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	UArpgAttributeSet* ArpgAttributeSet;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CharacterData")
	TSoftObjectPtr<UDataAsset_StartUpDataBasee> CharacterStartUpData;

	//~ Begin APawn Interface.
	virtual void PossessedBy(AController* NewController) override;
	//~ End APawn Interface

public:
	FORCEINLINE UArpgAbilitySystemComponent* GetArpgAbilitySystemComponent() const
	{
		return ArpgAbilitySystemComp;
	}

	FORCEINLINE UArpgAttributeSet* GetArpgAttributeSet() const
	{
		return ArpgAttributeSet;
	}
};
