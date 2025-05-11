// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAssets/Input/DataAsset_InputConfig.h"

UInputAction* UDataAsset_InputConfig::FindNativeInputActionByTag(const FGameplayTag& InInputTag) const
{
	for (const FARPGInputActionConfig& InputActionConfig : NativeInputActions)
	{
		/*��ǩƥ�䣺InputTag �����봫��� InInputTag ��ȫһ�¡�
			��Ч��У�飺InputAction ָ�����ǿգ����ⷵ����Ч��Դ��*/
		if (InputActionConfig.InputTag == InInputTag && InputActionConfig.InputAction)
		{
			return InputActionConfig.InputAction;
		}
	}

	return nullptr;
}
