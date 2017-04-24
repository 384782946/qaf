/*!
 * \file Singleton.h
 * \date 2016/07/21 22:30
 *
 * \author zxj
 * Contact: user@company.com
 *
 * \brief 
 *
 * single pattern implement
 *
 * \note
*/

#ifndef SINGLETON_H
#define SINGLETON_H

#include <QAtomicPointer>

template<typename T>
class Singleton
{
public:
	static T* getSingleton()
	{
		//test is object has been constructed
		if (!sInstancePtr.loadAcquire())
		{
			T* ptr = new T();
			//atomic operator
			if (!sInstancePtr.testAndSetOrdered(0, ptr))
			{
				//the object has been constructed
				//destruct the object you just apply 
				delete ptr;
			}
		}
		return sInstancePtr.loadAcquire();
	}

	static void release()
	{
		T* ptr = sInstancePtr.loadAcquire();
		if (ptr)
		{
			if (sInstancePtr.testAndSetOrdered(ptr, 0))
			{
				delete ptr;
			}
		}
	}

protected:
	//limit object construct and destruct
	Singleton(){}
	virtual ~Singleton(){}

private:
	//single object refused to copy
	Singleton(const Singleton&);
	Singleton& operator=(const Singleton&);
	 
	static QBasicAtomicPointer<T> sInstancePtr;
};

template<typename T>
QBasicAtomicPointer<T> Singleton<T>::sInstancePtr = Q_BASIC_ATOMIC_INITIALIZER(0);

#endif //SINGLETON_H
