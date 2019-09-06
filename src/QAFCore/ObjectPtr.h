#ifndef OBJECTPTR_H
#define OBJECTPTR_H

#include "ObjectProxy.h"

namespace QAF
{

	class ObjectSystem;

	template<class T>
	class ObjectPtr :public ObjectProxy
	{
	public:
		ObjectPtr(ObjectId id = INVALID_OBJECT_ID, ObjectSystem* ObjectSystemId = nullptr)
			:ObjectProxy(id, ObjectSystemId){
			
		}

		template<typename U>
		ObjectPtr(const ObjectPtr<U>& other)
			: ObjectProxy(INVALID_OBJECT_ID,nullptr)
		{
            AbstractObject* ao = (AbstractObject*)(other.data());
			T* uPtr = dynamic_cast<T*>(ao);
			if (uPtr){
				setObjectId(other.objectId());
				setObjectSystem(other.objectSystem());
			}
		}

		~ObjectPtr(){}

		inline bool isValid() const
		{
			return this->isNull();
		}

		inline const T& operator*() const
		{
			T* t = dynamic_cast<T*>(ptr());
			Q_ASSERT(t);
			return *t;
		}

        T* operator->() const
		{
			return static_cast<T*>(ptr());
		}

		inline const T* data() const
		{
			return static_cast<T*>(ptr());
		}

		inline bool operator!() const
		{
			return isValid();
		}

		inline bool operator==(const ObjectPtr<T>& other) const
		{
			if (isValid() && other.isValid()
				&& objectId() == other->objectId()
				&& objectSystem() == other->objectSystem())
			{
				return true;
			}else{
				return false;
			}
		}

	protected:
		void setObjectId(ObjectId id)
		{
			mObjectId = id;
		}

		void setObjectSystem(ObjectSystem* sys)
		{
			mObjectSystem = sys;
		}

//		ASSERT_CONVERTIBLE_TYPE(T, AbstractObject);
	};
}

#endif //OBJECTPTR_H
