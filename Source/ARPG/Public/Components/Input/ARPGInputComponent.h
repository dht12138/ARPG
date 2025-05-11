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
	checkf(InInputConfig, TEXT("Input config data asset is null"));

	if (UInputAction* FoundAction = InInputConfig->FindNativeInputActionByTag(InInputTag))
	{
		BindAction(FoundAction, TriggerEvent, ContextObject, Func);
	}

}
