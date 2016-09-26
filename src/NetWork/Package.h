#pragma once

#include "network_global.h"

#include <Qt>
#include <QByteArray>
#include <QDataStream>
#include <QHash>
#include <QSharedPointer>

#ifndef PACKAGE_VERSION
#define  PACKAGE_VERSION 1
#endif // !PACKAGE_VERSION

#define DECLARE_CLASS_NAME(class_name) static QByteArray className() { return #class_name;} \
			virtual QByteArray packageType() { return class_name::className(); }

struct PackageHeader
{
	qint16 Version;

	PackageHeader() : Version(PACKAGE_VERSION){}
};

class Package
{
public:
	Package(){}
	virtual ~Package(){}

	DECLARE_CLASS_NAME(Package)

	virtual bool pack(QDataStream& stream) = 0
	{
		stream << packageType() << mHeader.Version;
		return true;
	}

	virtual bool unpack(QDataStream& stream) = 0
	{
		stream >> mHeader.Version;
		return true;
	}

	qint16 version() const { return mHeader.Version; }

	void setVersion(qint16 version_) { mHeader.Version = version_; }

protected:
	PackageHeader mHeader;
};

class NETWORK_EXPORT ObjectFactory
{
public:
	template<typename T>
	static void registerClass()
	{
		constructors().insert(T::className(), &constructorHelper<T>);
	}

	static QSharedPointer<Package> createObject(const QByteArray& className);

private:
	typedef Package* (*Constructor)();

	template<typename T>
	static Package* constructorHelper()
	{
		return new T();
	}

	static QHash<QByteArray, Constructor>& constructors();
};
