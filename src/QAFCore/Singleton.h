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
	//����ʵ����
	Singleton(){}
	virtual ~Singleton(){}

private:
	//��ʵ������Ӧ�ô��ڿ���
	Singleton(const Singleton&);
	Singleton& operator=(const Singleton&);
	static std::auto_ptr<T> sInstance;
	static QMutex mMutex;
};

template<typename T>
std::auto_ptr<T> Singleton<T>::sInstance;

template<typename T>
QMutex Singleton<T>::mMutex;