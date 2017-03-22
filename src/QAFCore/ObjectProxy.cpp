#include "ObjectProxy.h"
#include "ObjectSystem.h"

namespace QAF
{

	ObjectProxy::ObjectProxy(ObjectId id, ObjectSystem* os)
		:mObjectSystem(os)
		, mObjectId(id)
	{
		if (id != 0 && os)
		{
			mObjectSystem->addObjectProxy(this);
		}
	}

	ObjectProxy::ObjectProxy(const ObjectProxy& other)
	{
		mObjectId = 0;
		mObjectSystem = nullptr;

		if (other.isNull())
		{
			mObjectSystem = other.mObjectSystem;
			mObjectId = other.mObjectId;
			mObjectSystem->addObjectProxy(this);
		}
	}

	ObjectProxy::~ObjectProxy()
	{
		if (isNull())
		{
			mObjectSystem->removeObjectProxy(this);
		}

		mObjectId = 0;
		mObjectSystem = nullptr;
	}

	bool ObjectProxy::isNull() const
	{
		if (!mObjectSystem)
			return false;

		if (mObjectId != 0)
			return (mObjectSystem->query(mObjectId) != nullptr);
		else
			return false;
	}

	ObjectProxy& ObjectProxy::operator=(const ObjectProxy& other)
	{
		if (isNull())
		{
			mObjectSystem->removeObjectProxy(this);
		}

		mObjectId = 0;
		mObjectSystem = nullptr;

		if (other.isNull())
		{
			mObjectSystem = other.mObjectSystem;
			mObjectId = other.mObjectId;
			mObjectSystem->addObjectProxy(this);
		}

		return *this;
	}

    AbstractObject* ObjectProxy::ptr() const
	{
		return mObjectSystem->query(mObjectId);
	}
}
