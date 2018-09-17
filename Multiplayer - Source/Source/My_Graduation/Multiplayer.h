// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UDPCommunication.h"
#include "UDPSend.h"
#include "UDPReceive.h"
#include "MyPlayerController.h"
#include "UDPObjects.h"
#include "ServerManager.h"
#include "Networking.h"
#include "Sockets.h"
#include "SocketSubsystem.h"
#include "Engine.h"
#include "Runtime/Sockets/Public/Sockets.h"
#include "Runtime/Sockets/Public/SocketSubsystem.h"
#include "Runtime/Sockets/Public/IPAddress.h"
#include <thread>
#include <chrono>
#include <future>
#include "Multiplayer.generated.h"

UCLASS()
class MY_GRADUATION_API AMultiplayer : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMultiplayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void WaitForConnect();

	UDPCommunication setMultiplayer;
	FString message[4] = { "ola", "como", "estas", "adeus" };

	AMyPlayerController *mycontroller;
	ServerManager server;
	UDPObjects object;

	std::thread sendThread;
	std::thread receiveThread;
	std::thread serverThread;
	std::thread connectThread;

	bool didSetOpponent = false;


	//bool running;
};
