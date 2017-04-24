#pragma once

#include "network_global.h"

#include <QHostAddress>

class Package;

class NETWORK_EXPORT UDPClient
{
public:
	UDPClient();
	~UDPClient();

	static void send(Package& package, const QHostAddress& address, int port);

private:

};

