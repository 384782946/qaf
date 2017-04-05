#include "ObjectSystem.h"

#include <QMutexLocker>

namespace QAF
{

	ObjectSystem::ObjectSystem(int sysId, QObject* parent)
		:AbstractSystem(sysId,parent)
		, mMinValidId(1)
		, mMaxValidId(1)
	{
		//TODO 实现ObjectModel
	}

	ObjectSystem::~ObjectSystem()
	{
		
	}

	void ObjectSystem::install()
	{
		AbstractSystem::install();
	}
	
	void ObjectSystem::uninstall()
	{
		AbstractSystem::uninstall();

		foreach(ObjectInfo* info, mObjects)
		{
			if (info)
			{
				foreach(ObjectProxy* op, info->mProxys)
				{
					if (op)
					{
						op->mObjectId = 0;
						op->mObjectSystem = nullptr;
					}
				}

				delete info->mObject;
				delete info;
				info = nullptr;
			}
		}

		mObjects.clear();
	}

    bool ObjectSystem::merge(ObjectSystem&)
	{
		return true;
	}

	ObjectId ObjectSystem::makeId()
	{
        QMutexLocker locker(&mMutex);
		ObjectId ret = 0;
		if (mMinValidId < mMaxValidId)
		{
			ret = mMinValidId;
			while (mMinValidId < mMaxValidId && hasObject(mMinValidId)) //确保id唯一
			{
				mMinValidId++;
			}
		}
		else
		{
			ret = mMaxValidId++;
			mMinValidId = mMaxValidId;
		}

		return ret;
	}

	void ObjectSystem::releaseId(ObjectId id)
	{
        QMutexLocker locker(&mMutex);
		if (mMaxValidId == id + 1)
			mMaxValidId = id;

		if (mMinValidId > id)
			mMinValidId = id;
	}

	bool ObjectSystem::hasObject(ObjectId id)
	{
		return id != INVALID_OBJECT_ID && mObjects.contains(id);
	}

	bool ObjectSystem::destory(ObjectId id)
	{
		if (hasObject(id))
		{
            //通知所有对象引用者，对象已销毁
			foreach(ObjectProxy* op, mObjects.value(id)->mProxys)
			{
				if (op)
				{
					op->mObjectId = 0;
				}
			}

			releaseId(id);
            return mObjects.remove(id) != 0;
		}
		else
		{
			return false;
		}
	}

	AbstractObject* ObjectSystem::query(ObjectId id)
	{
		if (hasObject(id))
		{
			return mObjects.value(id)->mObject;
		}

		return nullptr;
	}

	void ObjectSystem::addObjectProxy(ObjectProxy* op)
	{
		if (hasObject(op->mObjectId))
		{
			mObjects.value(op->mObjectId)->mProxys.append(op);
		}
	}

	void ObjectSystem::removeObjectProxy(ObjectProxy* op)
	{
		if (hasObject(op->mObjectId))
		{
			mObjects.value(op->mObjectId)->mProxys.removeOne(op);
			op->mObjectId = 0;
		}
	}

	bool ObjectSystem::changeId(ObjectId before, ObjectId after)
	{
		if (mObjects.contains(before) && !mObjects.contains(after) && after != INVALID_OBJECT_ID)
		{
			ObjectInfo* info = mObjects.value(before);
			if (info)
			{
				info->mObject->mObjectId = before;
				foreach(ObjectProxy* op, info->mProxys)
				{
					op->mObjectId = after;
				}

				mObjects.remove(before);
				mObjects.insert(after, info);
				return true;
			}
		}

		return true;
	}

	int ObjectSystem::objectCount()
	{
		return mObjects.size();
	}
}
