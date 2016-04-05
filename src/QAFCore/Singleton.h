/*!
 * \file Singleton.h
 * \date 2016/01/16 14:18
 *
 * \author zxj
 * Contact: user@company.com
 *
 * \brief 
 *
 *	实现了单例模式的抽象模板类,只需继承该类便拥有了单实例的特性
 *
 * \note
*/

#pragma once

#include <QAtomicPointer>

#include <QMutex>
#include <QMutexLocker>

template<typename T>
class Singleton
{
public:
	static T* getSingleton()
	{
#if QT_VERSION > QT_VERSION_CHECK(5, 0, 0)	                                          
		if (!sInstancePtr.loadAcquire())
		{
			T* ptr = new T();
			if (!sInstancePtr.testAndSetOrdered(0, ptr))
			{
				delete ptr;
			}
		}
		return sInstancePtr.loadAcquire();
#endif
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
	//不能实例化
	Singleton(){}
	virtual ~Singleton(){}

private:
	//单实例对象不应该存在拷贝
	Singleton(const Singleton&);
	Singleton& operator=(const Singleton&);
	
#if QT_VERSION > QT_VERSION_CHECK(5, 0, 0)	 
	static QBasicAtomicPointer<T> sInstancePtr;
#endif
};

#if QT_VERSION > QT_VERSION_CHECK(5, 0, 0)	 
template<typename T>
QBasicAtomicPointer<T> Singleton<T>::sInstancePtr = Q_BASIC_ATOMIC_INITIALIZER(0);
#endif