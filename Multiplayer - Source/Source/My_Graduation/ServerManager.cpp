// Fill out your copyright notice in the Description page of Project Settings.

#include "ServerManager.h"

ServerManager::ServerManager()
{
}

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
//TCP Client

OpponentAddress ServerManager::RegisterInServer()
{
	WSADATA wsaData;
	SOCKET ConnectSocket = INVALID_SOCKET;
	struct addrinfo *result = NULL,
		*ptr = NULL,
		hints;
	char *sendbuf = "HELLO\n";

	const char *sendInfo;
	const char *sendPort;
	std::string ipString;
	std::string portString;
	std::string infoString;
	//itoa(udpObjects.port, sendPort, 10);
	int test;
	test = udpObjects.port;
	portString = std::to_string(udpObjects.port);
	ipString = std::string(TCHAR_TO_UTF8(*udpObjects.address));
	infoString = ipString + portString;
	sendInfo = infoString.c_str();
	sendPort = portString.c_str();

	char recvbuf[512];
	int iResult;
	int recvbuflen = BUFFER_SIZE;


	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		print_red(10.f, "Failed to initialize Winsock!");
		return OpponentAddress(FString(""), 0);
	}

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	// Resolve the server address and port
	iResult = getaddrinfo(GAME_SERVER_ADDRESS.c_str(), GAME_SERVER_PORT.c_str(), &hints, &result);
	if (iResult != 0) {
		print_red(10.f, "Failed to resolve the server address and port!");
		WSACleanup();
		return OpponentAddress(FString(""), 0);
	}

	// Attempt to connect to an address until one succeeds
	for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {

		// Create a SOCKET for connecting to server
		ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype,
			ptr->ai_protocol);
		if (ConnectSocket == INVALID_SOCKET) {
			print_red(10.f, "Socket failed!");
			WSACleanup();
		}

		// Connect to server.
		iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
		if (iResult == SOCKET_ERROR) {
			closesocket(ConnectSocket);
			ConnectSocket = INVALID_SOCKET;
			continue;
		}
		break;
	}

	freeaddrinfo(result);

	if (ConnectSocket == INVALID_SOCKET) {
		print_red(10.f, "Unable to connect to server!");
		WSACleanup();
		return OpponentAddress(FString(""), 0);
	}

	//Send the UDP binded port to the server
	//IP is not necessary since the server can get the ip easily
	iResult = send(ConnectSocket, sendPort, strlen(sendPort), 0);
	if (iResult == SOCKET_ERROR) {
		print_red(10.f, "Send failed!");
		closesocket(ConnectSocket);
		WSACleanup();
		return OpponentAddress(FString(""), 0);
	}

	std::string msg2 = "Sent '" + std::to_string(iResult) + "' bytes.";
	print_yellow(10.f, msg2.c_str());

	/* shutdown the connection since no more data will be sent
	iResult = shutdown(ConnectSocket, SD_SEND);
	if (iResult == SOCKET_ERROR) {
	print_red(10.f, "Shutdown socket failed!");
	closesocket(ConnectSocket);
	WSACleanup();
	return OpponentAddress(FString(""), 0);
	}*/

	// Receive until the peer closes the connection
	do {

		//Receive the message sent from the server containing the IP and Port of the other player
		iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
		if (iResult > 0) {
			try {
				std::stringstream playerAnnouncement_ss(recvbuf);

				playerAnnouncement_ss >> playerAddress;
				playerAnnouncement_ss >> playerPort;

				peerManager.AddPeer(playerAddress, playerPort);

				std::string msg = "New player at '" + playerAddress + ":" + playerPort + "'.";
				print_green(5.f, msg.c_str());

				gotOpponent = true;

				return OpponentAddress(FString(playerAddress.c_str()), std::stoi(playerPort));
			}
			catch (...) {
				std::string msg = "New player announcement in WRONG FORMAT: '" + std::string(recvbuf) + "'.";
				print_red(10.f, msg.c_str());
			}

		}
		else if (iResult == 0) {
			print_red(10.f, "Connection closed!");
		}
		else {
			print_red(10.f, "Error on recv!");
		}

	} while (iResult > 0);

	// cleanup
	closesocket(ConnectSocket);
	WSACleanup();
	return OpponentAddress(FString(""), 0);
}




ServerManager::~ServerManager()
{
}
