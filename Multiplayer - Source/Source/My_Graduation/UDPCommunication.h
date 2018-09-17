// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Networking.h"
#include "Sockets.h"
#include "SocketSubsystem.h"
#include "Engine.h"
#include "Runtime/Sockets/Public/Sockets.h"
#include "Runtime/Sockets/Public/SocketSubsystem.h"
#include "Runtime/Sockets/Public/IPAddress.h"
#include <string>
#include <thread>
#include <chrono>


/**
 * 
 */
class MY_GRADUATION_API UDPCommunication
{
public:
	UDPCommunication();
	~UDPCommunication();

	//functions
	bool Connection(FString& serverAddress, int32 portNumber);
	bool SendMessage(FString Message, FString opponentIp, int32 opponentPort);
	FString ReceiveMessage();



	bool binded;
	bool messageSent;
	bool messageReceived;


	//variables
	FSocket *Socket;// = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(NAME_DGram, TEXT("MySocket"), true);
	TSharedPtr<FInternetAddr> address;

	FString ipAddress = "10.72.1.20";
	//FString ipAddress = "193.136.164.196";
	//FString ipAddress2 = "192.168.1.9";
	FIPv4Address ip;
	//FIPv4Address ip2;
	int32 port = 32003;
	//int32 port2 = 20001;
	
	

};
