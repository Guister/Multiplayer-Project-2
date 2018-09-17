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
#include <PeerManager.h>
#include "UDPCommunication.h"
#include "OpponentAddress.h"
#include "UDPObjects.h"
#include "ServerManagerActor.generated.h"


UCLASS()
class MY_GRADUATION_API AServerManagerActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AServerManagerActor();

	//const std::string GAME_SERVER_ADDRESS = "194.210.134.223";
	const std::string GAME_SERVER_ADDRESS = "127.0.0.1";
	const std::string GAME_SERVER_PORT = "31000";

	const int BUFFER_SIZE = 512; // bytes

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	// A boolean to keep track if the game is running or not
	bool IsRunning;

	// A pointer to the thread that will be doing the networking
	std::thread *NetworkThread;

	// This peer manager will keep track of our peers!
	PeerManager peerManager;

	// A frame counter to show peers on frames that are multiples of 1000
	unsigned long long int frameCounter;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	std::string playerPort;
	std::string playerAddress;


	UDPObjects udpObjects;
	
};
