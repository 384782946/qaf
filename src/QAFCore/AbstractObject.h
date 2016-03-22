/*!
 * \file AbstractObject.h
 * \date 2016/01/16 14:18
 *
 * \author zxj
 * Contact: user@company.com
 *
 * \brief 
 *
 * 所有系统中可分配对象的基类
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
	/* 由于使用了Qt实现的运行时类型识别机制		*/
	/*所有继承自该类的子类务必添加Q_OBJECT		*/
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
		AbstractObject(ObjectId parent = INVALID_OBJECT_ID); //限制构造
		AbstractObject(const AbstractObject& other); //限制拷贝
		virtual ~AbstractObject() = 0;

	private:
		AbstractObject& operator=(const AbstractObject&); //禁止复制

		ObjectId mObjectId;
		ObjectId mParentId;
	};
}