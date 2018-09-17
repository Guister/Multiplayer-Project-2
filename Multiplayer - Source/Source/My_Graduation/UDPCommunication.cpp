// Fill out your copyright notice in the Description page of Project Settings.

#include "UDPCommunication.h"

// Some custom macros to log stuff on screen
#define print_white(duration, text)	if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, duration, FColor::White, text); }
#define print_yellow(duration, text) if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, duration, FColor::Yellow, text); }
#define print_red(duration, text) if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, duration, FColor::Red, text); }
#define print_green(duration, text)	if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, duration, FColor::Green, text); }
#define print_blue(duration, text) if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, duration, FColor::Blue, text); }

UDPCommunication::UDPCommunication()
{
}


bool UDPCommunication::Connection(FString& serverAddress, int32 portNumber)
{
	ipAddress = serverAddress;
	port = portNumber;

	//Create socket
	Socket = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(NAME_DGram, TEXT("MySocket"), true);
	Socket->SetNonBlocking(true);
	Socket->SetBroadcast(true);
	Socket->SetReuseAddr(true);
	Socket->SetRecvErr(true);

	UE_LOG(LogTemp, Warning, TEXT("Socket created(?)"));

	FIPv4Address::Parse(ipAddress, ip);

	address = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
	address->SetIp(ip.Value);
	address->SetPort(portNumber);

	//Bind it to an address
	binded = Socket->Bind(*address);
	if (binded == true)
	{
		UE_LOG(LogTemp, Warning, TEXT("Binded: true"));
		return true;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Binded: false"));
		return false;
	}
}
bool UDPCommunication::SendMessage(FString Message, FString opponentIp, int32 opponentPort)
{
	TCHAR *serializedMessage = Message.GetCharArray().GetData();
	int32 size = FCString::Strlen(serializedMessage);
	int32 Sent = 0;

	FString ipAddress2 = opponentIp;
	//FString ipAddress2 = "127.0.0.1";
	FIPv4Address ip2;
	int32 port2 = opponentPort;


	TSharedPtr<FInternetAddr> address2;

	FIPv4Address::Parse(ipAddress2, ip2);


	address2 = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
	address2->SetIp(ip2.Value);
	address2->SetPort(port2);

	//Send message to target address
	messageSent = Socket->SendTo((uint8*)TCHAR_TO_UTF8(serializedMessage), size, Sent, *address2);
	if (messageSent == true && Sent > 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Message sent"));
		return true;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Message not sent"));
		return false;
	}
}
FString UDPCommunication::ReceiveMessage()
{
	uint32 Size;
	TArray<uint8> ReceivedData;
	TSharedRef<FInternetAddr> targetAddress = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
	if (Socket->HasPendingData(Size) == true)
	{
		UE_LOG(LogTemp, Warning, TEXT("Has data to receive"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No data"));
	}
	while (Socket->HasPendingData(Size))
	{
		ReceivedData.SetNumUninitialized(FMath::Min(Size, 65507u));
		int32 Read;
		//Receive message
		messageReceived = Socket->RecvFrom(ReceivedData.GetData(), ReceivedData.Num(), Read, *targetAddress);
		if (messageReceived == true)
		{
			UE_LOG(LogTemp, Warning, TEXT("Message Received"));
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Message was not received"));
		}
	}
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Data Read! %d"), ReceivedData.Num()));
	//return StringFromBinaryArray(ReceivedData);

	//Return the data to a FString
	FString data;
	const std::string cstr(reinterpret_cast<const char*>(ReceivedData.GetData()), ReceivedData.Num());
	data += FString(cstr.c_str());
	//UE_LOG(LogTemp, Warning, TEXT("message:%s"), *data);
	return data;
}
UDPCommunication::~UDPCommunication()
{
	//ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(Socket);
}
