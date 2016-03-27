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
	//����ʵ����
	Singleton(){}
	//static QMutex mMutex;

private:
	//��ʵ������Ӧ�ô��ڿ���
	Singleton(const Singleton&);
	Singleton& operator=(const Singleton&);
};