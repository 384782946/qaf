#ifndef OBJECTSYSTEM_H
#define OBJECTSYSTEM_H

#include "AbstractObject.h"
#include "ObjectPtr.h"
#include "AbstractSystem.h"

#include <QHash>
#include <QMutex>

namespace QAF
{
	class QAFCORE_EXPORT ObjectSystem :
		public AbstractSystem
	{
		friend class ObjectProxy;

		Q_OBJECT

	public:
		ObjectSystem(int sysId, QObject* parent = 0);
		~ObjectSystem();

		virtual void install();
		virtual void uninstall();

		template<class T, class ...Args>
		ObjectPtr<T> create(Args... args)
		{
			AbstractObject* obj = new T(args...);
			ObjectId id = makeId();
			obj->mObjectId = id;
			ObjectInfo* info = new ObjectInfo();
			info->mObject = obj;
			mObjects.insert(id, info);
			return ObjectPtr<T>(id, this);
		}

		template<class T>
		ObjectPtr<T> clone(const ObjectPtr<T>& other)
		{
			AbstractObject* obj = new T(*other);
			ObjectId id = makeId();
			obj->mObjectId = id;
			ObjectInfo* info = new ObjectInfo();
			info->mObject = obj;
			mObjects.insert(id, info);
			return ObjectPtr<T>(id, this);
		}

		template<class T>
		ObjectPtr<T> object(ObjectId id)
		{
			T* p = qobject_cast<T*>(query(id));
			if (p)
				return ObjectPtr<T>(id, this);
			else
				return ObjectPtr<T>();
		}

		bool merge(ObjectSystem&);
		bool destory(ObjectId);
        bool hasObject(ObjectId);
        int objectCount();

	protected:
        ObjectId makeId();
        void releaseId(ObjectId);
		bool changeId(ObjectId before, ObjectId after);
		AbstractObject* query(ObjectId);

		void addObjectProxy(ObjectProxy*);
		void removeObjectProxy(ObjectProxy*);

	private:

		struct ObjectInfo
		{
			AbstractObject* mObject;
			QList<ObjectProxy*> mProxys;

			ObjectInfo()
			{
				mObject = nullptr;
			}
		};

        //竞争性资源
		QHash<ObjectId, ObjectInfo*> mObjects;
		ObjectId mMinValidId;
		ObjectId mMaxValidId;
        QMutex mMutex;
	};
}

#endif //OBJECTSYSTEM_H
