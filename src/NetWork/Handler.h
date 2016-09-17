#pragma once

class Package;

class Handler
{
public:
	virtual QSharedPointer<Package> doHandle(QSharedPointer<Package>) = 0;
};

