// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "DataAsset_InputConfig.generated.h"

class UInputAction;
class UInputMappingContext;


//USTRUCT(BlueprintType)��
//�����ýṹ��Ϊ UE ����ϵͳ ֧�ֵ� USTRUCT��������ͼ����Ϊ��������ʹ�á�
//֧���ڱ༭�����������ʲ���������ԣ��п��ӻ����á�
USTRUCT(BlueprintType)
struct FARPGInputActionConfig
{
	GENERATED_BODY()
	//	����꣬�������� UE ��������л����롣

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (Categories = "InputTag"))
	FGameplayTag InputTag;
	/*meta = (Categories = "InputTag")��
		�ڱ༭���й��˱�ǩ������ʾ InputTag �����µı�ǩ���������ð�ȫ�ԡ�*/

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
	/*��ĳ�� �ṹ�壨USTRUCT�� �� �ࣨUCLASS�� �ڱ༭���б�չʾΪ�б���������ʲ��е�����Ԫ�ء���ͼ�еı����б�ʱ��
	Ĭ������£��༭����ֱ����ʾ�ýṹ������������������ FARPGInputActionConfig����������ʾ��ʽ����ֱ�ۣ�
	�������ڽṹ������������ʱ���޷�����ʶ��ÿ��Ԫ�ص����ݡ�
		ͨ�� TitleProperty������ָ��һ��������Ϊ�ýṹ�����ġ����⡱���ñ༭����������Ե�ֵ���Ĭ�ϵ���������*/

	UInputAction* FindNativeInputActionByTag(const FGameplayTag& InInputTag) const;




};
