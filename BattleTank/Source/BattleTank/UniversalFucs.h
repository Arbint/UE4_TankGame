// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/Engine.h"
#include "UObject/NoExportTypes.h"
#include "UniversalFucs.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API UUniversalFucs : public UObject
{
	GENERATED_BODY()
public:
	static void ScreenMessage(FString Message, float time = 5.0f, FColor Color = FColor::Cyan);
	
	
};
