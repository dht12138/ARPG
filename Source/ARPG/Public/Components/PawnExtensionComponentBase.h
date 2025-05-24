// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PawnExtensionComponentBase.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ARPG_API UPawnExtensionComponentBase : public UActorComponent
{
	GENERATED_BODY()

public:	


protected:
	template <class T>
	T* GetOwningPawn() const
	{
		static_assert(TPointerIsConvertibleFromTo<T, APawn>::Value,
			"'T' Template parameter to GetPawn must be derived from APawn");
		/*TPointerIsConvertibleFromTo<T, APawn>：UE 类型特性工具，检查 T* 是否能隐式转换为 APawn* 。
			静态断言（Static_Assert）：若 T 不是 APawn 派生类，编译报错，阻止无效类型使用。*/

		return CastChecked<T>(GetOwner());
	}

	APawn* GetOwningPawn() const
	{
		return GetOwningPawn<APawn>();
	}

	template <class T>
	T* GetOwningController() const
	{
		static_assert(TPointerIsConvertibleFromTo<T, AController>::Value,
			"'T' Template parameter to GetController must be derived from AController");

		return GetOwningPawn<APawn>()->GetController<T>();
	}

public:	

	
};
