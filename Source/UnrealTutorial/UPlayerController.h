// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UnrealTutorial.h"
#include "GameFramework/PlayerController.h"
#include "UPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class UNREALTUTORIAL_API AUPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	virtual void PostInitializeComponents() override;
	virtual void OnPossess(APawn* aPawn) override;//UE4 4.22부터는 기존의 Possess는 상속을 받을수 없게 되어있다. 대신 OnPossess라는 함수를 똑같이 이용하면 된다.
};
