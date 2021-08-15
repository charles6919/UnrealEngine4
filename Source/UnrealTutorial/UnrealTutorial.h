// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"

DECLARE_LOG_CATEGORY_EXTERN(UnrealTutorial, Log, All);
#define ULOG_CALLINFO (FString(__FUNCTION__) + TEXT("(") + FString::FromInt(__LINE__)+TEXT(")"))
#define ULOG_S(Verbosity) UE_LOG(UnrealTutorial, Verbosity, TEXT("%s"), *ULOG_CALLINFO)
#define ULOG(Verbosity, Format, ...) UE_LOG(UnrealTutorial, Verbosity, TEXT("%s %s"), *ULOG_CALLINFO, *FString::Printf(Format, ##__VA_ARGS__))

