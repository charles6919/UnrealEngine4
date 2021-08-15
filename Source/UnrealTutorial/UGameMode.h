// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UnrealTutorial.h"
#include "GameFramework/GameModeBase.h"
#include "UGameMode.generated.h"

/**
 * 
 */
UCLASS()
class UNREALTUTORIAL_API AUGameMode : public AGameModeBase
{
	GENERATED_BODY()

	AUGameMode();

public:
	virtual void PostLogin(APlayerController* NewPlayer) override;
};
