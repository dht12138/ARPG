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

//输入动作绑定：根据输入标签（InInputTag）从数据资产（InInputConfig）中查找对应的输入动作（UInputAction），并将其绑定到指定的回调函数。
//
//类型泛化支持：通过模板参数 UserObject 和 CallbackFunc，支持任意类型的上下文对象和回调函数。
//
//安全校验：检查输入配置有效性，避免空指针崩溃。
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
