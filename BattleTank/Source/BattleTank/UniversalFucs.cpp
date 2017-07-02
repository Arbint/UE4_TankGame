// Fill out your copyright notice in the Description page of Project Settings.

#include "UniversalFucs.h"




void UUniversalFucs::ScreenMessage(FString Message, float time /*= 5.0f*/, FColor Color /*= FColor::Cyan*/)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, time, Color, Message);
	}
}
