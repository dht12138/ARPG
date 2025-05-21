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
			//��DataAsset�ļ�����ӵ�ASC
		}
	}

}

void AARPGHeroCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{

	checkf(InputConfigDA, TEXT("Forgot to assign value data asset as input config"));

	ULocalPlayer* LocalPlayer = GetController<APlayerController>()->GetLocalPlayer();

	UEnhancedInputLocalPlayerSubsystem* Subsystem = 
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);
	/*��ϵͳ���ã�������ҵ�����ӳ�������ģ����ȼ������ӡ��Ƴ���*/
		
	check(Subsystem);

	Subsystem->AddMappingContext(InputConfigDA->DefaultMappingContext, 0);
	/*ӳ�������� Mapping Context : �������붯���������� / �豸�İ󶨹�ϵ��
		���ȼ����� 0����ֵԽ�����ȼ�Խ�ͣ������ȼ������Ŀɸ��ǵ����ȼ�������󶨣���ս��״̬����̽��״̬����*/

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
	/*�������¼�����ȡ��ά����ֵ����WASD��ҡ�����룩��
		FVector2D�ṹ��X���Ӧ�������루A / D��ҡ�����ң���Y���Ӧǰ�����루W / S ��ҡ�����£�
		���뷶Χ��ͨ��Ϊ[-1, 1]��1 ��ʾ�������룬 - 1 ��ʾ�������롣*/

	const FRotator MovementRotation(0.f, Controller->GetControlRotation().Yaw, 0.f);
	/*��ȡ������ˮƽ��ת����Yaw������Pitch��Roll����ȷ���ƶ��������ɫ�ӽǷ���һ�¡�
		ʾ��������ɫ����������Yaw = 0�㣩��ǰ������Ϊ(1, 0, 0)����ת�򶫷���Yaw = 90�㣩��ǰ��������Ϊ(0, 1, 0)��*/

	if (MovementVector.Y != 0.f)
	{
		const FVector ForwardDirection = MovementRotation.RotateVector(FVector::ForwardVector);
		/*
			FVector::ForwardVector ��ȫ������ϵ��(1, 0, 0)��
			RotateVector ��ȫ��ǰ����ת��Ϊ������Yaw���򣨽�ɫ�泯���򣩡�
			Y > 0����ɫ���ӽ���ǰ���ƶ���
			Y < 0����ɫ���ӽ������ƶ�*/
		AddMovementInput(ForwardDirection, MovementVector.Y);
		/*�����뷽���ǿ�ȴ��ݸ���ɫ�ƶ�������� UCharacterMovementComponent����
			������������׼������ƶ�������(0.7, 0.7, 0) ��ʾб���ƶ�����
			ǿ��ֵ������ֵ�ķ��ȣ��� 1.0 ��ʾȫ���ƶ���0.5 ��ʾ���٣���*/
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
