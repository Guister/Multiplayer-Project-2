// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include <utility>
#include <string>
#include <list>

typedef std::pair<std::string, std::string> peer;

/**
 * 
 */
class MY_GRADUATION_API PeerManager
{
public:
	PeerManager();
	~PeerManager();
	void AddPeer(std::string ipAddr, std::string port);
	void LogPeers();

protected:
	std::list<peer> myPeers;
};
