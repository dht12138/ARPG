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
		/*	OwnerActor：处理网络权限和逻辑归属（如技能冷却、资源消耗）。
			示例：PlayerState 作为 Owner 可防止角色销毁后技能状态丢失。
			AvatarActor：处理视觉效果和世界交互（如命中检测、粒子特效）。*/

		//触发断点
		ensureMsgf(!CharacterStartUpData.IsNull(), TEXT("StartUp DataAsset Is NULL : %s"), *GetName());
	}
}


