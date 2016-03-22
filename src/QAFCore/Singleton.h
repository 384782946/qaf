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

//#include <QMutex>
//#include <QMutexLocker>

template<typename T>
class Singleton
{
public:
	virtual ~Singleton(){}

	static T* getSingleton()
	{
		//QMutexLocker locker(&mMutex);
		static T singleton;
		return &singleton;
	}

protected:
	//不能实例化
	Singleton(){}
	//static QMutex mMutex;

private:
	//单实例对象不应该存在拷贝
	Singleton(const Singleton&);
	Singleton& operator=(const Singleton&);
};