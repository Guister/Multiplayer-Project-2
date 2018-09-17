// Fill out your copyright notice in the Description page of Project Settings.

#include "UDPSend.h"

std::mutex cv_m;

UDPSend::UDPSend()
{
}


void UDPSend::SendData(AMyPlayerController *playerController)
{
	while (runSend == true)
	{
		//UE_LOG(LogTemp, Warning, TEXT("qwe"));
		//cv_m.lock();
		myPositionX = FString::SanitizeFloat(playerController->playerPosition.X);
		myPositionY = FString::SanitizeFloat(playerController->playerPosition.Y);
		myPositionZ = FString::SanitizeFloat(playerController->playerPosition.Z);

		myRotationX = FString::SanitizeFloat(playerController->playerRotation.Pitch);
		myRotationY = FString::SanitizeFloat(playerController->playerRotation.Yaw);
		myRotationZ = FString::SanitizeFloat(playerController->playerRotation.Roll);

		message.Append(myPositionX);
		message.Append(",");
		message.Append(myPositionY);
		message.Append(",");
		message.Append(myPositionZ);
		message.Append(",");

		message.Append(myRotationX);
		message.Append(",");
		message.Append(myRotationY);
		message.Append(",");
		message.Append(myRotationZ);
		message.Append(",");

		UE_LOG(LogTemp, Warning, TEXT("%s"), *message);
		//int32 port = 10000;
		//FString address = "127.0.0.1";
		//Communication.Connection(address, port);
//		Communication.SendMessage(message);
		message.Empty();
		//cv_m.unlock();
		std::this_thread::sleep_for(std::chrono::seconds(5));
	}
}



UDPSend::~UDPSend()
{
}
