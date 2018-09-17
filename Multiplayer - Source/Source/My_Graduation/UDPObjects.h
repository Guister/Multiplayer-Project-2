// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UDPCommunication.h"
#include "MyPlayerController.h"
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <chrono>

/**
 * 
 */
class MY_GRADUATION_API UDPObjects
{
public:
	UDPObjects();
	~UDPObjects();

	FString myPositionX;
	FString myPositionY;
	FString myPositionZ;

	FString myRotationX;
	FString myRotationY;
	FString myRotationZ;

	FString myBallPositionX;
	FString myBallPositionY;
	FString myBallPositionZ;

	FString myBallRotationX;
	FString myBallRotationY;
	FString myBallRotationZ;

	float xPosition;
	float yPosition;
	float zPosition;

	float xRotation;
	float yRotation;
	float zRotation;

	float xBallPosition;
	float yBallPosition;
	float zBallPosition;

	float xBallRotation;
	float yBallRotation;
	float zBallRotation;

	int32 port = 32003;
	FString address = "10.72.1.20";
	//FString address = "193.136.164.196";

	FString messageSent;
	FString messageReceived;
	TArray<FString> positionAndRotation;

	UDPCommunication Communication;

	bool runSend = false;

	bool runReceive = false;

	void SetConnection();
	void SendData(AMyPlayerController *playerController, FString opponentIp, int32 opponentPort);
	void ReceiveData(AMyPlayerController *playerController);
};
