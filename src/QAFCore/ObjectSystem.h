﻿#ifndef OBJECTSYSTEM_H
#define OBJECTSYSTEM_H

#include <QHash>
#include <QMutex>
#include <QSharedPointer>

#include "AbstractObject.h"
#include "ObjectPtr.h"
#include "AbstractSystem.h"

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
            QSharedPointer<ObjectInfo> info = QSharedPointer<ObjectInfo>(new ObjectInfo());
			info->mObject = obj;
			mObjects.insert(id, info);
			return ObjectPtr<T>(id, this);
		}

        template<class T, class ...Args>
        QList<ObjectPtr<T>> createArray(int count)
        {
            typename QList<ObjectPtr<T>> rets;
            if(count>0){
                QList<ObjectId> ids = makeArrayId(count);
                //void* memBuff = malloc(count*sizeof(typename T));
                for(int i = 0;i<count;++i){
                    AbstractObject* obj = new T();
                    ObjectId id = ids.at(i);
                    obj->mObjectId = id;
                    QSharedPointer<ObjectInfo> info = QSharedPointer<ObjectInfo>(new ObjectInfo());
                    info->mObject = obj;
                    mObjects.insert(id, info);
                    rets.append(ObjectPtr<T>(id, this));
                }
            }

            return rets;
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
            T* p = dynamic_cast<T*>(query(id));
			if (p)
				return ObjectPtr<T>(id, this);
			else
				return ObjectPtr<T>();
		}

        int objectCount() const;
        bool hasObject(ObjectId) const;
        QList<ObjectId> objects() const;

		bool merge(ObjectSystem&);
        bool destory(ObjectId);

	protected:
        ObjectId makeId();
        //针对大批量分配做优化
        QList<ObjectId> makeArrayId(int count);
        void releaseId(ObjectId);
		bool changeId(ObjectId before, ObjectId after);
		AbstractObject* query(ObjectId);

		void addObjectProxy(ObjectProxy*);
		void removeObjectProxy(ObjectProxy*);

    protected:

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
        QHash<ObjectId, QSharedPointer<ObjectInfo>> mObjects;
		ObjectId mMinValidId;
		ObjectId mMaxValidId;
        QMutex mMutex;
	};
}

#endif //OBJECTSYSTEM_H
