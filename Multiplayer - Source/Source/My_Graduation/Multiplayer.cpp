// Fill out your copyright notice in the Description page of Project Settings.

#include "Multiplayer.h"

// Some custom macros to log stuff on screen
#define print_white(duration, text)	if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, duration, FColor::White, text); }
#define print_yellow(duration, text) if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, duration, FColor::Yellow, text); }
#define print_red(duration, text) if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, duration, FColor::Red, text); }
#define print_green(duration, text)	if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, duration, FColor::Green, text); }
#define print_blue(duration, text) if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, duration, FColor::Blue, text); }

// Sets default values
AMultiplayer::AMultiplayer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AMultiplayer::WaitForConnect()
{
	//int32 port = 10000;
	//FString address = "127.0.0.1";
	//FString address = "194.210.134.225";
	//setMultiplayer.Connection(address, port);
	receiveThread = std::thread(&UDPObjects::ReceiveData, object, mycontroller);


}

// Called when the game starts or when spawned
void AMultiplayer::BeginPlay()
{
	Super::BeginPlay();

	serverThread = std::thread(&ServerManager::RegisterInServer, &server);

	object.SetConnection();

	object.runSend = true;
	object.runReceive = true;

	mycontroller = Cast<AMyPlayerController>(GetWorld()->GetFirstPlayerController());

	WaitForConnect();
}

// Called every frame
void AMultiplayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	/*
	if (server.gotOpponent) {
		print_white(1.0f, "server.gotOpponent=true");
	} else {
		print_white(1.0f, "server.gotOpponent=false");
	}

	if (didSetOpponent) {
		print_white(1.0f, "didSetOpponent=true");
	}
	else {
		print_white(1.0f, "didSetOpponent=false");
	}*/

	if (server.gotOpponent && !didSetOpponent) {
		// Set the opponent address and port
		print_green(4.0f, "Got an opponent! Starting thread.");
		sendThread = std::thread(&UDPObjects::SendData, object, mycontroller, FString(server.playerAddress.c_str()), std::stoi(server.playerPort));
		didSetOpponent = true;
		
	}

	//setMultiplayer.ReceiveMessage();
	//setMultiplayer.SendMessage(message[2]);
	
}

void AMultiplayer::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	object.runSend = false;
	object.runReceive = false;
	print_green(4.f, "EndPlay called! Threadqwe should now stop.");
	sendThread.detach();
	receiveThread.detach();
	serverThread.detach();
	print_green(4.f, "EndPlay qweqwecalled! Threadqwe should now stop.");

	// The game has ended, save that so that the thread knows when to stop
}
