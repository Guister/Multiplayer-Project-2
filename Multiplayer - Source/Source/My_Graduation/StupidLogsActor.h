// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <thread>
#include <chrono>
#include "StupidLogsActor.generated.h"

UCLASS()
class MY_GRADUATION_API AStupidLogsActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStupidLogsActor();
	void Print();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	// A pointer to the thread that will be doing the logs
	std::thread *LoggerThread;

	// A function to do some stupid logs
	void DoStupidLogs();

	// A boolean to keep track if the game is running or not
	bool IsRunning;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
