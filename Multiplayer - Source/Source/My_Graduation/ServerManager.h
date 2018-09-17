// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AllowWindowsPlatformTypes.h"			// Unreal does not like
#include <winsock2.h>							// 		winsock2.h nor
#include <windows.h>							// 		windows.h
#include <Ws2tcpip.h>							//		for inet_pton()
#include "HideWindowsPlatformTypes.h"			// 		so we need to surround them with Allow- and HideWindowsPlatformTypes.h
#include <stdio.h>
#include <string>
#include <thread>
#include <utility>
#include <sstream>
#include <exception>
#include <PeerManager.h>
#include "UDPCommunication.h"
#include "OpponentAddress.h"
#include "UDPObjects.h"

/**
 * 
 */
class MY_GRADUATION_API ServerManager
{
public:
	ServerManager();
	~ServerManager();

	//const std::string GAME_SERVER_ADDRESS = "194.210.134.223";
	//const std::string GAME_SERVER_ADDRESS = "193.136.154.112";
	const std::string GAME_SERVER_ADDRESS = "10.72.1.20";
	const std::string GAME_SERVER_PORT = "31000";



	const int BUFFER_SIZE = 512; // bytes

protected:

	// This peer manager will keep track of our peers!
	PeerManager peerManager;

	// A frame counter to show peers on frames that are multiples of 1000
	unsigned long long int frameCounter;

public:

	std::string playerPort;
	std::string playerAddress;
	bool gotOpponent = false;


	UDPObjects udpObjects;
	// Registers our client in the game server as interested to receive new player updates
	OpponentAddress RegisterInServer();

};