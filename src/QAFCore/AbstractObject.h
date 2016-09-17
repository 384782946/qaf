/*!
 * \file AbstractObject.h
 * \date 2016/07/22
 *
 * \author zxj
 *
 * \brief 
 *		base class for all system object
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

	typedef unsigned int ObjectId;

	/************************************************************************/
	/* 由于使用了Qt实现的运行时类型识别机制		*/
	/*所有继承自该类的子类务必添加Q_OBJECT		*/
	/************************************************************************/
	class QAFCORE_EXPORT AbstractObject :public QObject
	{
		//Q_OBJECT
		Q_PROPERTY(QString name READ name WRITE setName)
		Q_PROPERTY(ObjectId id READ id)

		friend class ObjectSystem;

	public:

		/*!
		* \fn	getParent
		* \brief 
		*		get parent object
		* \param 
		*		void
		* \return
		*		parent object's id,or INVALID_OBJECT_ID if no parent
		*/
		ObjectId getParent();

		/*!
		* \fn	setParent
		* \brief 
		*		set parent object
		* \param 
		*		id of parent object
		* \return
		*		void
		*/
		void setParent(ObjectId parent = INVALID_OBJECT_ID);

		/*!
		* \fn	name
		* \brief 
		*		get object's name
		* \param 
		*		void
		* \return
		*		object's name
		*/
		QString	name() const;

		/*!
		* \fn	setName
		* \brief 
		*		set object's name
		* \param 
		*		name
		* \return
		*		void
		*/
		void setName(const QString & name);

		/*!
		* \fn	id
		* \brief 
		*		get object's unique id
		* \param 
		*		void
		* \return
		*		object's id(greater than zero),or INVALID_OBJECT_ID if object invalid
		*/
		ObjectId id() const;

		/*!
		* \fn	pack
		* \brief 
		*		virtual method to convert object to stream
		* \param 
		*		output stream
		* \return
		*		void
		*/
		virtual void pack(QDataStream& stream) const;

		/*!
		* \fn	unpack
		* \brief 
		*		virtual method to construct object from stream
		* \param 
		*		
		* \return
		*		
		*/
		virtual void unpack(QDataStream& stream);

	protected:
		/*!
		* \fn	AbstractObject
		* \brief 
		*		refuse to call constructor outside of the class
		* \param 
		*		object's unique id
		* \return
		*		void
		*/
		AbstractObject(ObjectId parent = INVALID_OBJECT_ID);

		/*!
		* \fn	AbstractObject
		* \brief
		*		refuse to call copy constructor outside of the class
		* \param
		*		other object instance
		* \return
		*		void
		*/
		AbstractObject(const AbstractObject& other);

		/*!
		* \fn	~AbstractObject
		* \brief
		*		object's destructor 
		* \param
		*		void
		* \return
		*		void
		*/
		virtual ~AbstractObject() = 0;

		/*!
		* \fn	isSerializable
		* \brief
		*		whether this object can be serialize,default is false.
		* \param
		*		void
		* \return
		*		void
		*/
		virtual bool isSerializable() const{ return false; }

	private:
		/*!
		* \fn	operator=
		* \brief
		*		refuse to assign everywhere
		* \param
		*		other object instance
		* \return
		*		void
		*/
		AbstractObject& operator=(const AbstractObject&);

		///object's id
		ObjectId mObjectId;
		///parent object's id
		ObjectId mParentId;
	};
}