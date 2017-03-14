#include "Package.h"

#include "BaseException.h"

QSharedPointer<Package> ObjectFactory::createObject(const QByteArray& className)
{
	ObjectFactory::Constructor constructor = constructors().value(className, nullptr);
	if (constructor == NULL)
	{
		EXCEPTION_SIMPLE_THROW(QLogicException, "Can not create object before regist this type.");
		return QSharedPointer<Package>();
	}

    return QSharedPointer<Package>(constructor());
}

QHash<QByteArray, ObjectFactory::Constructor>& ObjectFactory::constructors()
{
	static QHash<QByteArray, ObjectFactory::Constructor> instance;
	return instance;
}
