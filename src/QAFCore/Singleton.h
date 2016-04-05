/*!
 * \file Singleton.h
 * \date 2016/01/16 14:18
 *
 * \author zxj
 * Contact: user@company.com
 *
 * \brief 
 *
 *	ʵ���˵���ģʽ�ĳ���ģ����,ֻ��̳и����ӵ���˵�ʵ��������
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
	//����ʵ����
	Singleton(){}
	virtual ~Singleton(){}

private:
	//��ʵ������Ӧ�ô��ڿ���
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