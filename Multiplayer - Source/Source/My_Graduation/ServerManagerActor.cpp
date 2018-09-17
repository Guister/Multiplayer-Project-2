// Fill out your copyright notice in the Description page of Project Settings.

#include "ServerManagerActor.h"
#include <EngineGlobals.h>
#include <Runtime/Engine/Classes/Engine/Engine.h>
#include <sstream>
#include <exception>

// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

// Some custom macros to log stuff on screen
#define print_white(duration, text)	if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, duration, FColor::White, text); }
#define print_yellow(duration, text) if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, duration, FColor::Yellow, text); }
#define print_red(duration, text) if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, duration, FColor::Red, text); }
#define print_green(duration, text)	if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, duration, FColor::Green, text); }
#define print_blue(duration, text) if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, duration, FColor::Blue, text); }

// Sets default values
AServerManagerActor::AServerManagerActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AServerManagerActor::BeginPlay()
{
	Super::BeginPlay();

	// The game is starting, set it to be running
	IsRunning = true;

	// And start the networking thread, keeping only a pointer to it
	//NetworkThread = new std::thread(&AServerManagerActor::RegisterInServer, this);

	frameCounter = 0;	
}

void AServerManagerActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	// The game has ended, save that so that the thread knows when to stop
	IsRunning = false;
	print_green(10.f, "yay");

}
// Called every frame
void AServerManagerActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (frameCounter % 600 == 0) {
		peerManager.LogPeers();
	}

	frameCounter++;
}

