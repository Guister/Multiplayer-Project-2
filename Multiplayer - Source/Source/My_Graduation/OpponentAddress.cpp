// Fill out your copyright notice in the Description page of Project Settings.

#include "OpponentAddress.h"


//To avoid circular dependecy
OpponentAddress::OpponentAddress(FString opIp, int32 opPort)
{
	opponentIp = opIp;
	opponentPort = opPort;
}

OpponentAddress::~OpponentAddress()
{
}
