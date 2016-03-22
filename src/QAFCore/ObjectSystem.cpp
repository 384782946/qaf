#include "ObjectSystem.h"

namespace QAF
{

	ObjectSystem::ObjectSystem(int sysId, QObject* parent)
		:AbstractSystem(sysId,parent)
		, mMinValidId(1)
		, mMaxValidId(1)
	{
		//TODO ʵ��ObjectModel
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
						op->mObjectSystem = NULL;
					}
				}

				delete info->mObject;
				delete info;
				info = NULL;
			}
		}

		mObjects.clear();
	}

	bool ObjectSystem::merge(ObjectSystem& os)
	{
		return true;
	}

	ObjectId ObjectSystem::makeId()
	{
		ObjectId ret = 0;
		if (mMinValidId < mMaxValidId)
		{
			ret = mMinValidId;
			while (mMinValidId < mMaxValidId && hasObject(mMinValidId)) //ȷ��idΨһ
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
			//֪ͨ�������屻����
			AbstractObject* ao = mObjects.value(id)->mObject;
			foreach(ObjectProxy* op, mObjects.value(id)->mProxys)
			{
				if (op)
				{
					op->mObjectId = 0;
				}
			}

			releaseId(id);
			return mObjects.remove(id);
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

		return NULL;
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