#ifndef OBJECTPROXY_H
#define OBJECTPROXY_H

#include "qafcore_global.h"
#include "AbstractObject.h"

namespace QAF
{
	class ObjectSystem;

	class QAFCORE_EXPORT ObjectProxy
	{
		friend class ObjectSystem;

	public:
		ObjectProxy(ObjectId id, ObjectSystem* ObjectSystemId);
		ObjectProxy(const ObjectProxy&);
		virtual ~ObjectProxy();

        bool isNull() const;
		ObjectProxy& operator=(const ObjectProxy&);

		ObjectId objectId() const
		{
			return mObjectId;
		}

		ObjectSystem* objectSystem() const
		{
			return mObjectSystem;
		}
		
	protected:
		AbstractObject* ptr() const;

	protected:
		ObjectId mObjectId;
		ObjectSystem* mObjectSystem;
	};
}

#endif //OBJECTPROXY_H
