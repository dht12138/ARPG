// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAssets/Input/DataAsset_InputConfig.h"

UInputAction* UDataAsset_InputConfig::FindNativeInputActionByTag(const FGameplayTag& InInputTag) const
{
	for (const FARPGInputActionConfig& InputActionConfig : NativeInputActions)
	{
		/*标签匹配：InputTag 必须与传入的 InInputTag 完全一致。
			有效性校验：InputAction 指针必须非空，避免返回无效资源。*/
		if (InputActionConfig.InputTag == InInputTag && InputActionConfig.InputAction)
		{
			return InputActionConfig.InputAction;
		}
	}

	return nullptr;
}
