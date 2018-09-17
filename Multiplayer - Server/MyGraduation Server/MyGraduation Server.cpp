// MyGraduation Server.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <ws2tcpip.h>
#include <utility>
#include <chrono>
#include <thread>
#include <stdio.h>
#include <string.h>
#include <list>

#pragma comment (lib, "ws2_32.lib")
typedef std::pair <const char *, const char *> info;

const int BUFFER_SIZE = 512;

int numberOfConnectedClients = 0;
std::string playerOneIp;
std::string playerOnePort;
std::string playerTwoIp;
std::string playerTwoPort;


void ExchangeMessage(sockaddr_in client, SOCKET clientSocket)
{
	char ip[INET_ADDRSTRLEN];
	inet_ntop(AF_INET, &(client.sin_addr), ip, INET_ADDRSTRLEN);

	char host[NI_MAXHOST];
	char service[NI_MAXHOST];

	ZeroMemory(host, NI_MAXHOST);
	ZeroMemory(service, NI_MAXHOST);

	if (getnameinfo((sockaddr*)&client, sizeof(client), host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0)
	{
		std::cout << host << " connected on port" << service << " from ip:" << ip << std::endl;
	}
	else
	{
		inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
		std::cout << host << " connected on port" << ntohs(client.sin_port) << std::endl;
	}

	char buff[512];
	int bufflen = BUFFER_SIZE;

	int bytesReceived = recv(clientSocket, buff, bufflen, 0);
	buff[bytesReceived] = '\0';
	std::cout << "Received '" << bytesReceived << "' bytes: " << buff << std::endl;


	std::list<info> data;
	std::string msgToSend;

	if (numberOfConnectedClients == 1) {
		// We are player one
		playerOneIp = std::string(ip);
		playerOnePort = std::string(buff);

		while (numberOfConnectedClients != 2) {
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}
		//save the ip and port
		data.push_back(info(playerTwoIp.c_str(), playerTwoPort.c_str()));
		msgToSend = std::string(data.back().first) + " " + std::string(data.back().second);

		send(clientSocket, msgToSend.c_str(), msgToSend.length(), 0);
	}
	else {
		// We are player two
		playerTwoIp = std::string(ip);
		playerTwoPort = std::string(buff);
		//save the ip and port
		data.push_back(info(playerOneIp.c_str(), playerOnePort.c_str()));
		msgToSend = std::string(data.back().first) + " " + std::string(data.back().second);

		send(clientSocket, msgToSend.c_str(), msgToSend.length(), 0);

	}
	//close socket
	//closesocket(listening);

	/*
	char buf[4096];

	while (true)
	{
		ZeroMemory(buf, 4096);
		int bytesReceived = recv(clientSocket, buf, 4096, 0);
		if (bytesReceived == SOCKET_ERROR)
		{
			std::cerr << "Error in rtcv()" << std::endl;
			break;
		}

		if (bytesReceived == 0)
		{
			std::cout << "Client dc" << std::endl;
			break;
		}
		//echo message
		send(clientSocket, buf, bytesReceived + 1, 0);
	}
		*/

}

void main()
{
	WSADATA wsData;
	WORD ver = MAKEWORD(2, 2);

	int ws0k = WSAStartup(ver, &wsData);
	if (ws0k != 0)
	{
		std::cerr << "Can't initiate socket" << std::endl;
		return;
	}

	//Create socket
	SOCKET listening = socket(AF_INET, SOCK_STREAM, 0);
	if (listening == INVALID_SOCKET)
	{
		std::cerr << "Can't create a socket" << std::endl;
		return;
	}

	//Bind socket
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(31000);
	hint.sin_addr.S_un.S_addr = INADDR_ANY;

	bind(listening, (sockaddr*)&hint, sizeof(hint));

	listen(listening, SOMAXCONN);

	//wait for connection
	sockaddr_in client;
	int clientSize = sizeof(client);
	SOCKET clientSocket;
	std::thread* myThread;

	while (true) {
		clientSocket = accept(listening, (sockaddr*)&client, &clientSize);
		numberOfConnectedClients++;
		myThread = new std::thread(ExchangeMessage, client, clientSocket);
	}

	//closesocket(clientSocket);

	//WSACleanup();
}

