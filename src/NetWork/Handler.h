#pragma once

class Package;

struct ReqeustContext
{
	QHostAddress Address;
	quint16 Port;
};

class Handler
{
public:
	virtual QSharedPointer<Package> doHandle(const ReqeustContext&,QSharedPointer<Package>) = 0;
};

