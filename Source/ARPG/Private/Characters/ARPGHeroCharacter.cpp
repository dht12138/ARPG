// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/ARPGHeroCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputSubsystems.h"
#include "DataAssets/Input/DataAsset_InputConfig.h"
#include "Components/Input/ARPGInputComponent.h"
#include "ARPGGameplayTags.h"
#include "AbilitySystem/ArpgAbilitySystemComponent.h"
#include "DataAssets/StartUpDatta/DataAsset_StartUpDataBasee.h"

#include "ARPGDebugHelper.h"

AARPGHeroCharacter::AARPGHeroCharacter()   
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 200.f;
	CameraBoom->SocketOffset = FVector(0.f, 55.f, 65.f);
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 500.f, 0.f);
	GetCharacterMovement()->MaxWalkSpeed = 400.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

}

void AARPGHeroCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	/*if (ArpgAbilitySystemComp && ArpgAttributeSet)
	{
		const FString ASCTEST = FString::Printf(TEXT("Owner actor : %s, Avatar actor : %s"),
			*ArpgAbilitySystemComp->GetOwnerActor()->GetActorLabel(), 
			*ArpgAbilitySystemComp->GetAvatarActor()->GetActorLabel());
		Debug::Print(TEXT("Ability system component valid.") + ASCTEST, FColor::Green);
		Debug::Print(TEXT("AttributeSet valid."), FColor::Green);
	}*/

	if (!CharacterStartUpData.IsNull())
	{
		if (UDataAsset_StartUpDataBasee* LoadedData = CharacterStartUpData.LoadSynchronous())
		{
			LoadedData->GiveToAbilitySystemComponent(ArpgAbilitySystemComp);
			//将DataAsset的技能添加到ASC
		}
	}

}

void AARPGHeroCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{

	checkf(InputConfigDA, TEXT("Forgot to assign value data asset as input config"));

	ULocalPlayer* LocalPlayer = GetController<APlayerController>()->GetLocalPlayer();

	UEnhancedInputLocalPlayerSubsystem* Subsystem = 
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);
	/*子系统作用：管理玩家的输入映射上下文（优先级、叠加、移除）*/
		
	check(Subsystem);

	Subsystem->AddMappingContext(InputConfigDA->DefaultMappingContext, 0);
	/*映射上下文 Mapping Context : 定义输入动作与物理按键 / 设备的绑定关系。
		优先级参数 0：数值越低优先级越低，高优先级上下文可覆盖低优先级的输入绑定（如战斗状态覆盖探索状态）。*/

	UARPGInputComponent* ARPGInputComp = CastChecked<UARPGInputComponent>(PlayerInputComponent);

	ARPGInputComp->BindNativeInputAction(InputConfigDA, ARPGGameplayTags::InputTag_Move,
		ETriggerEvent::Triggered, this, &ThisClass::Input_Move);

	ARPGInputComp->BindNativeInputAction(InputConfigDA, ARPGGameplayTags::InputTag_Look,
		ETriggerEvent::Triggered, this, &ThisClass::Input_Look);


}

void AARPGHeroCharacter::BeginPlay()
{
	Super::BeginPlay();

}

void AARPGHeroCharacter::Input_Move(const FInputActionValue& InputActionVal)
{
	const FVector2D MovementVector = InputActionVal.Get<FVector2D>();
	/*从输入事件中提取二维向量值（如WASD或摇杆输入）。
		FVector2D结构：X轴对应左右输入（A / D或摇杆左右），Y轴对应前后输入（W / S 或摇杆上下）
		输入范围：通常为[-1, 1]，1 表示正向输入， - 1 表示反向输入。*/

	const FRotator MovementRotation(0.f, Controller->GetControlRotation().Yaw, 0.f);
	/*获取控制器水平旋转（仅Yaw，忽略Pitch和Roll），确保移动方向与角色视角方向一致。
		示例：若角色面向正北（Yaw = 0°），前方向量为(1, 0, 0)；若转向东方（Yaw = 90°），前方向量变为(0, 1, 0)。*/

	if (MovementVector.Y != 0.f)
	{
		const FVector ForwardDirection = MovementRotation.RotateVector(FVector::ForwardVector);
		/*
			FVector::ForwardVector 是全局坐标系的(1, 0, 0)。
			RotateVector 将全局前方向转换为控制器Yaw方向（角色面朝方向）。
			Y > 0：角色向视角正前方移动。
			Y < 0：角色向视角正后方移动*/
		AddMovementInput(ForwardDirection, MovementVector.Y);
		/*将输入方向和强度传递给角色移动组件（如 UCharacterMovementComponent）。
			方向向量：标准化后的移动方向（如(0.7, 0.7, 0) 表示斜向移动）。
			强度值：输入值的幅度（如 1.0 表示全速移动，0.5 表示半速）。*/
	}
	if (MovementVector.X != 0)
	{
		const FVector RightDirection = MovementRotation.RotateVector(FVector::RightVector);
		AddMovementInput(RightDirection, MovementVector.X);
	}

}

void AARPGHeroCharacter::Input_Look(const FInputActionValue& InputActionVal)
{
	const FVector2D LookAxisVector = InputActionVal.Get<FVector2D>();

	if (LookAxisVector.X != 0.f)
	{
		AddControllerYawInput(LookAxisVector.X);
	}

	if (LookAxisVector.Y != 0.f)
	{
		AddControllerPitchInput(LookAxisVector.Y);
	}
}
