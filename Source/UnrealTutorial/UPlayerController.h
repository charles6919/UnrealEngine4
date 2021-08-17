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
	virtual void OnPossess(APawn* aPawn) override;//UE4 4.22���ʹ� ������ Possess�� ����� ������ ���� �Ǿ��ִ�. ��� OnPossess��� �Լ��� �Ȱ��� �̿��ϸ� �ȴ�.
};
