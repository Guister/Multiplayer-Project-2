// Fill out your copyright notice in the Description page of Project Settings.
#include "StupidLogsActor.h"
#include <EngineGlobals.h>
#include <Runtime/Engine/Classes/Engine/Engine.h>

// Some custom macros to log stuff on screen
#define print_white(duration, text)	if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, duration, FColor::White, text); }
#define print_yellow(duration, text) if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, duration, FColor::Yellow, text); }
#define print_red(duration, text) if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, duration, FColor::Red, text); }
#define print_green(duration, text)	if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, duration, FColor::Green, text); }
#define print_blue(duration, text) if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, duration, FColor::Blue, text); }

//CLass just for testing
// Sets default values
AStupidLogsActor::AStupidLogsActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AStupidLogsActor::BeginPlay()
{
	Super::BeginPlay();

	// The game is starting, set it to be running
	IsRunning = true;

	// And start the logger thread, keeping only a pointer to it
	LoggerThread = new std::thread(&AStupidLogsActor::DoStupidLogs, this);

	//Testing append
	FString name = "ola";
	FString name2 = "adeus";
	name.Append("a");
	name.Append("b");
	name.Append(name2);

	print_red(4.f, name);

	FString message23 = "o:l:a";
	TArray<FString> message24;
	//message23 = setMultiplayer.ReceiveMessage();
	//message23.Append("aa");
	message23.ParseIntoArray(message24, TEXT(":"), true);
	print_yellow(4.f, message24[0]);
	print_yellow(4.f, message24[1]);
	print_yellow(4.f, message24[2]);
	
}

// Called whenever this actor is being removed from a level
void AStupidLogsActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	// The game has ended, save that so that the thread knows when to stop
	IsRunning = false;
	print_green(4.f, "EndPlay called! Thread should now stop.");
}

void AStupidLogsActor::DoStupidLogs()
{

	while (IsRunning) {
		print_red(4.5f, "Thread is running!");
		std::this_thread::sleep_for(std::chrono::seconds(5));
	}

	print_red(4.5f, "Thread stopping.");
}

void AStupidLogsActor::Print()
{
	UE_LOG(LogTemp, Warning, TEXT("Funciona"));
}

// Called every frame
void AStupidLogsActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
