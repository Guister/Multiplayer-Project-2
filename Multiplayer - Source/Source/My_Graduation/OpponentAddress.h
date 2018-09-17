// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class MY_GRADUATION_API OpponentAddress
{
public:
	FString opponentIp;
	int32 opponentPort;

	OpponentAddress(FString opIp, int32 opPort);
	~OpponentAddress();
};
