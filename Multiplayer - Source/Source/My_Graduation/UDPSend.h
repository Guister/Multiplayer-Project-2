// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UDPCommunication.h"
#include "MyPlayerController.h"
#include "StupidLogsActor.h"
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <chrono>

/**
 * 
 */
class MY_GRADUATION_API UDPSend
{
public:
	UDPSend();
	~UDPSend();

	FString myPositionX;
	FString myPositionY;
	FString myPositionZ;

	FString myRotationX;
	FString myRotationY;
	FString myRotationZ;

	FString message;

	UDPCommunication Communication;

	bool runSend = false;

	//std::mutex cv_m;

	void SendData(AMyPlayerController *playerController);
};
