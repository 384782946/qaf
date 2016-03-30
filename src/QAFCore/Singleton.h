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

#include <QMutex>
#include <QMutexLocker>

template<typename T>
class Singleton
{
public:
	static T* getSingleton()
	{
		if (!sInstance.get())
		{
			QMutexLocker locker(&mMutex);
			if (!sInstance.get())
			{
				sInstance.reset(new T());
			}
			
		}
		return sInstance.get();
	}

	static void release()
	{
		QMutexLocker locker(&mMutex);
		sInstance.release();
	}

protected:
	//不能实例化
	Singleton(){}
	virtual ~Singleton(){}

private:
	//单实例对象不应该存在拷贝
	Singleton(const Singleton&);
	Singleton& operator=(const Singleton&);
	static std::auto_ptr<T> sInstance;
	static QMutex mMutex;
};

template<typename T>
std::auto_ptr<T> Singleton<T>::sInstance;

template<typename T>
QMutex Singleton<T>::mMutex;