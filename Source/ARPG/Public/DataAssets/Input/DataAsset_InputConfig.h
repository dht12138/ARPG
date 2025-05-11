// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "DataAsset_InputConfig.generated.h"

class UInputAction;
class UInputMappingContext;


//USTRUCT(BlueprintType)：
//声明该结构体为 UE 反射系统 支持的 USTRUCT，可在蓝图中作为变量类型使用。
//支持在编辑器（如数据资产、组件属性）中可视化配置。
USTRUCT(BlueprintType)
struct FARPGInputActionConfig
{
	GENERATED_BODY()
	//	必需宏，用于生成 UE 反射和序列化代码。

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (Categories = "InputTag"))
	FGameplayTag InputTag;
	/*meta = (Categories = "InputTag")：
		在编辑器中过滤标签，仅显示 InputTag 分类下的标签，提升配置安全性。*/

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* InputAction;


};

/**
 * 
 */
UCLASS()
class ARPG_API UDataAsset_InputConfig : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputMappingContext* DefaultMappingContext;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = ( TitleProperty = "InputTag"))
	TArray<FARPGInputActionConfig> NativeInputActions;
	/*当某个 结构体（USTRUCT） 或 类（UCLASS） 在编辑器中被展示为列表项（如数据资产中的数组元素、蓝图中的变量列表）时，
	默认情况下，编辑器会直接显示该结构体或类的类型名（例如 FARPGInputActionConfig）。这种显示方式不够直观，
	尤其是在结构体包含多个属性时，无法快速识别每个元素的内容。
		通过 TitleProperty，可以指定一个属性作为该结构体或类的“标题”，让编辑器用这个属性的值替代默认的类型名。*/

	UInputAction* FindNativeInputActionByTag(const FGameplayTag& InInputTag) const;




};
