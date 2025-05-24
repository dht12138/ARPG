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
		/*TPointerIsConvertibleFromTo<T, APawn>��UE �������Թ��ߣ���� T* �Ƿ�����ʽת��Ϊ APawn* ��
			��̬���ԣ�Static_Assert������ T ���� APawn �����࣬���뱨����ֹ��Ч����ʹ�á�*/

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
