// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/ARPGBaseCharacter.h"
#include "AbilitySystem/ArpgAbilitySystemComponent.h"
#include "AbilitySystem/ArpgAttributeSet.h"

// Sets default values
AARPGBaseCharacter::AARPGBaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	GetMesh()->bReceivesDecals = false;

	ArpgAbilitySystemComp = CreateDefaultSubobject<UArpgAbilitySystemComponent>(TEXT("ArpgAbilitySystemComp"));

	ArpgAttributeSet = CreateDefaultSubobject<UArpgAttributeSet>(TEXT("ArpgAttributeSet"));



}

UAbilitySystemComponent* AARPGBaseCharacter::GetAbilitySystemComponent() const
{
	return GetArpgAbilitySystemComponent();
}

void AARPGBaseCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (ArpgAbilitySystemComp)
	{
		ArpgAbilitySystemComp->InitAbilityActorInfo(this, this);
		/*	OwnerActor����������Ȩ�޺��߼��������缼����ȴ����Դ���ģ���
			ʾ����PlayerState ��Ϊ Owner �ɷ�ֹ��ɫ���ٺ���״̬��ʧ��
			AvatarActor�������Ӿ�Ч�������罻���������м�⡢������Ч����*/

		//�����ϵ�
		ensureMsgf(!CharacterStartUpData.IsNull(), TEXT("StartUp DataAsset Is NULL : %s"), *GetName());
	}
}


