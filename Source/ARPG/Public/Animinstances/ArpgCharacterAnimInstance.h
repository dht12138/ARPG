// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animinstances/ArpgBaseAnimInstance.h"
#include "ArpgCharacterAnimInstance.generated.h"

class AARPGBaseCharacter;
class UCharacterMovementComponent;
/**
 * 
 */
UCLASS()
class ARPG_API UArpgCharacterAnimInstance : public UArpgBaseAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeInitializeAnimation() override;
	/*ʼ������ʵ����
		��������ͼ�״δ��������³�ʼ��ʱ��NativeInitializeAnimation() �ᱻ�Զ����ã�
		�������ö���ϵͳ�ĳ�ʼ״̬���绺�����á���ʼ�������ȣ���
		�����ͼ�е� Event Initialize Animation ��
		�� C++ ��ʵ��������ͼ�ڵ� Event Initialize Animation �Ĺ��ܣ������ܸ��ߣ��ʺϸ����߼���*/

	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;
	/*  ����			NativeThreadSafeUpdateAnimation		NativeUpdateAnimation
		ִ���߳�		�����̣߳��̰߳�ȫ��					��Ϸ�̣߳����̰߳�ȫ��
		����Ӱ��		���ͣ���������Ϸ�߼���					�ϸߣ�������Ϸ�̣߳�
		���ݷ�������	ֻ�ܷ����̰߳�ȫ�ı����ͺ���				�ɷ������г�Ա�����ͺ���
		������;		�������Ͷ����߼������ٶȡ�������㣩		��Ҫ������Ϸ״̬�ķ��̰߳�ȫ�߼�*/

protected:
	UPROPERTY()
	AARPGBaseCharacter* OwningChar;

	UPROPERTY()
	UCharacterMovementComponent* OwningMovementComp;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimData|LocomotionData")
	float GroundSpeed;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimData|LocomotionData")
	bool bHasAcceleration;


};
