#include "AbstractObject.h"
#include <QDataStream>

namespace QAF
{
	AbstractObject::AbstractObject(ObjectId parent/* = INVALID_OBJECT_ID*/)
		:QObject(nullptr)
		, mParentId(parent)
	{
		//�����ж���ϵͳ�ӹܣ���˲���Ϊ����
		//���ݲ����Է�ֹ��Qt��������ͷ�
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