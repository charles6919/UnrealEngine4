// Fill out your copyright notice in the Description page of Project Settings.


#include "UPlayerController.h"

void AUPlayerController::BeginPlay()
{
	Super::BeginPlay();

	//게임 모드로 들어가도록 하는 함수
	FInputModeGameOnly InputMode;
	SetInputMode(InputMode);
}

void AUPlayerController::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	ULOG_S(Warning);
}

void AUPlayerController::OnPossess(APawn* aPawn)
{
	ULOG_S(Warning);
	Super::OnPossess(aPawn);
}
