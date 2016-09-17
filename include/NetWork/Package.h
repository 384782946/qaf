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
	qint32 Length;
	qint8 Version;

	PackageHeader() :Length(0), Version(PACKAGE_VERSION){}
};

class Package
{
public:

	DECLARE_CLASS_NAME(Package)

	virtual bool pack(QDataStream& stream) = 0
	{
		stream << packageType() << mHeader.Length << mHeader.Version;
		return true;
	}

	virtual bool unpack(QDataStream& stream) = 0
	{
		stream >> mHeader.Length >> mHeader.Version;
		return true;
	}

	qint32 lenth() const { return mHeader.Length; }

	qint8 version() const { return mHeader.Version; }

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
