#include "AbstractObject.h"
#include <QDataStream>

namespace QAF
{
	AbstractObject::AbstractObject(ObjectId parent/* = INVALID_OBJECT_ID*/)
		:QObject(nullptr)
		, mParentId(parent)
	{
		//由于有对象系统接管，因此不再为父类
		//传递参数以防止被Qt管理机制释放
	}

	AbstractObject::AbstractObject(const AbstractObject& other)
	{
		mObjectId = other.mObjectId;
		mParentId = other.mParentId;
	}

	AbstractObject::~AbstractObject()
	{
	}

	ObjectId AbstractObject::getParent()
	{
		return mParentId;
	}

	void AbstractObject::setParent(ObjectId parent/* = INVALID_OBJECT_ID*/)
	{
		mParentId = parent;
	}

	QString	AbstractObject::name() const
	{
		return this->objectName();
	}

	void AbstractObject::setName(const QString & name)
	{
		this->setObjectName(name);
	}

	ObjectId AbstractObject::id() const
	{
		return mObjectId;
	}

	void AbstractObject::pack(QDataStream& stream) const
	{
		stream << mObjectId
			<< mParentId;
	}

	void AbstractObject::unpack(QDataStream& stream)
	{
		stream >> mObjectId
			>> mParentId;
	}
}