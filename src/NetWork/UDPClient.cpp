#include "UDPClient.h"

#include <QUdpSocket>

#include "Package.h"

UDPClient::UDPClient()
{
}


UDPClient::~UDPClient()
{
}

void UDPClient::send(Package& package, const QHostAddress& address, int port)
{
	QByteArray data;
	QDataStream outStream(&data, QIODevice::WriteOnly);
	outStream.setVersion(QDataStream::Qt_5_6);
	package.pack(outStream);

	QUdpSocket socket;
	socket.writeDatagram(data, address, port);
}
