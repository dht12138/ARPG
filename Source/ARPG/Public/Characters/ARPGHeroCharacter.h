// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/ARPGBaseCharacter.h"
#include "ARPGHeroCharacter.generated.h"


class USpringArmComponent;
class UCameraComponent;

/**
 * 
 */
UCLASS()
class ARPG_API AARPGHeroCharacter : public AARPGBaseCharacter
{
	GENERATED_BODY()
	
public:
	AARPGHeroCharacter();

protected:
	virtual void BeginPlay() override;

private:
#pragma region Components
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "ture"))
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "ture"))
	UCameraComponent* FollowCamera;


#pragma endregion


};
