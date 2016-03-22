/*!
 * \file AbstractObject.h
 * \date 2016/01/16 14:18
 *
 * \author zxj
 * Contact: user@company.com
 *
 * \brief 
 *
 * ����ϵͳ�пɷ������Ļ���
 *
 * \note
*/

#pragma once

#include <QObject>
#include "Serializable.h"
#include "QAFGlobal.h"
#include "qafcore_global.h"

#define INVALID_OBJECT_ID 0

namespace QAF
{
	class ObjectMemory;

	typedef int ObjectId;

	/************************************************************************/
	/* ����ʹ����Qtʵ�ֵ�����ʱ����ʶ�����		*/
	/*���м̳��Ը��������������Q_OBJECT		*/
	/************************************************************************/
	class QAFCORE_EXPORT AbstractObject :public QObject,public Serializable
	{
		Q_OBJECT
		Q_PROPERTY(QString name READ name WRITE setName)
		Q_PROPERTY(ObjectId id READ id)

		friend class ObjectSystem;

	public:
		ObjectId getParent();
		void setParent(ObjectId parent = INVALID_OBJECT_ID);

		QString	name() const;
		void setName(const QString & name);

		inline ObjectId id() const;

		virtual void pack(QDataStream& stream) const;
		virtual void unpack(QDataStream& stream);

	protected:
		AbstractObject(ObjectId parent = INVALID_OBJECT_ID); //���ƹ���
		AbstractObject(const AbstractObject& other); //���ƿ���
		virtual ~AbstractObject() = 0;

	private:
		AbstractObject& operator=(const AbstractObject&); //��ֹ����

		ObjectId mObjectId;
		ObjectId mParentId;
	};
}