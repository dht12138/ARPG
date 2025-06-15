// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "DataAssets/Input/DataAsset_InputConfig.h"
#include "ARPGInputComponent.generated.h"


/**
 * 
 */
UCLASS()
class ARPG_API UARPGInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()
	
public:

	template<class UserObject, typename CallbackFunc>
	void BindNativeInputAction(const UDataAsset_InputConfig* InInputConfig, const FGameplayTag& InInputTag,
		ETriggerEvent TriggerEvent, UserObject* ContextObject, CallbackFunc Func);

	template<class UserObject, typename CallbackFunc>
	void BindAbilityInputAction(const UDataAsset_InputConfig* InInputConfig, UserObject* ContextObject,
		CallbackFunc InputPressedFunc, CallbackFunc InputRelasedFunc);

};

//���붯���󶨣����������ǩ��InInputTag���������ʲ���InInputConfig���в��Ҷ�Ӧ�����붯����UInputAction����������󶨵�ָ���Ļص�������
//
//���ͷ���֧�֣�ͨ��ģ����� UserObject �� CallbackFunc��֧���������͵������Ķ���ͻص�������
//
//��ȫУ�飺�������������Ч�ԣ������ָ�������
template<class UserObject, typename CallbackFunc>
inline void UARPGInputComponent::BindNativeInputAction(const UDataAsset_InputConfig* InInputConfig,
	const FGameplayTag& InInputTag, ETriggerEvent TriggerEvent, UserObject* ContextObject, CallbackFunc Func)
{
	checkf(InInputConfig, TEXT("Input config data asset is null, error in BindNativeInputAction"));

	if (UInputAction* FoundAction = InInputConfig->FindNativeInputActionByTag(InInputTag))
	{
		BindAction(FoundAction, TriggerEvent, ContextObject, Func);
	}

}

template<class UserObject, typename CallbackFunc>
inline void UARPGInputComponent::BindAbilityInputAction(const UDataAsset_InputConfig* InInputConfig, 
	UserObject* ContextObject, CallbackFunc InputPressedFunc, CallbackFunc InputRelasedFunc)
{
	checkf(InInputConfig, TEXT("Input config data asset is null, error in BindAbilityInputAction"));

	for (const FARPGInputActionConfig& AbilityInputActionConfig : InInputConfig->AbilityInputActions)
	{
		if(!AbilityInputActionConfig.IsValid()) continue;

		BindAction(AbilityInputActionConfig.InputAction, ETriggerEvent::Started, ContextObject,
			InputPressedFunc, AbilityInputActionConfig.InputTag);

		BindAction(AbilityInputActionConfig.InputAction, ETriggerEvent::Completed, ContextObject,
			InputRelasedFunc, AbilityInputActionConfig.InputTag);
	}
}
