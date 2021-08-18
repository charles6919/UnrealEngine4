// Fill out your copyright notice in the Description page of Project Settings.


#include "UGameMode.h"
#include "UCharacter.h"
#include "UPlayerController.h"

AUGameMode::AUGameMode()
{
	DefaultPawnClass = AUCharacter::StaticClass();
	PlayerControllerClass = AUPlayerController::StaticClass();
}

void AUGameMode::PostLogin(APlayerController* NewPlayer)
{
	ULOG(Warning, TEXT("PostLogin Begin."));
	Super::PostLogin(NewPlayer);
	ULOG(Warning, TEXT("PostLogin End."));
}
