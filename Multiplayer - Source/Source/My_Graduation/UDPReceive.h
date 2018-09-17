// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UDPCommunication.h"
#include "MyPlayerController.h"
#include <thread>
#include <queue>
#include <mutex>

/**
 * 
 */
class MY_GRADUATION_API UDPReceive
{
public:
	UDPReceive();
	~UDPReceive();

	FString messageReceived;
	TArray<FString> positionAndRotation;

	float xPosition;
	float yPosition;
	float zPosition;

	float xRotation;
	float yRotation;
	float zRotation;

	bool runReceive = false;

	UDPCommunication Communication;

	void ReceiveData(AMyPlayerController *playerController);
};
