// Fill out your copyright notice in the Description page of Project Settings.

#include "PeerManager.h"

// Some custom macros to log stuff on screen
#include <EngineGlobals.h>
#include <Runtime/Engine/Classes/Engine/Engine.h>
#define print_white(duration, text)	if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, duration, FColor::White, text); }
#define print_yellow(duration, text) if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, duration, FColor::Yellow, text); }
#define print_red(duration, text) if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, duration, FColor::Red, text); }
#define print_green(duration, text)	if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, duration, FColor::Green, text); }
#define print_blue(duration, text) if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, duration, FColor::Blue, text); }

PeerManager::PeerManager()
{
}

PeerManager::~PeerManager()
{
}

void PeerManager::AddPeer(std::string ipAddr, std::string port)
{
	peer newPeer(ipAddr, port);
	myPeers.push_back(newPeer);
}

void PeerManager::LogPeers()
{
	//Log all the players connected to the server
	for (peer p : myPeers) {
		std::string peerInfo = "Peer: '" + p.first + ":" + p.second + "'";
		print_blue(4.f, peerInfo.c_str());
	}

	print_blue(4.f, "Logging all known peers:");
}