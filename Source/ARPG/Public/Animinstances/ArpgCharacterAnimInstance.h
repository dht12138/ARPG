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
	/*始化动画实例：
		当动画蓝图首次创建或重新初始化时，NativeInitializeAnimation() 会被自动调用，
		用于设置动画系统的初始状态（如缓存引用、初始化变量等）。
		替代蓝图中的 Event Initialize Animation ：
		在 C++ 中实现类似蓝图节点 Event Initialize Animation 的功能，但性能更高，适合复杂逻辑。*/

	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;
	/*  特性			NativeThreadSafeUpdateAnimation		NativeUpdateAnimation
		执行线程		动画线程（线程安全）					游戏线程（非线程安全）
		性能影响		更低（不阻塞游戏逻辑）					较高（依赖游戏线程）
		数据访问限制	只能访问线程安全的变量和函数				可访问所有成员变量和函数
		典型用途		纯计算型动画逻辑（如速度、方向计算）		需要访问游戏状态的非线程安全逻辑*/

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
