/*!
 * \file AbstractSystem.h
 * \date 2016/01/16 14:24
 *
 * \author zxj
 * Contact: user@company.com
 *
 * \brief 
 *
 * 所有系统的基类，为系统定义接口
 *
 * \note
*/

#ifndef ABSTRACTSYSTEM_H
#define ABSTRACTSYSTEM_H

#include "QAFGlobal.h"
#include <QObject>

namespace QAF
{
	class AbstractSystem : public QObject
	{
	public:
		AbstractSystem(int systemId,QObject* parent = 0)
			:QObject(parent)
			, mSystemId(systemId)
		{
		}

		virtual ~AbstractSystem()
		{
		}

        virtual void install(){ setInstalled(true); }

        virtual void uninstall(){ setInstalled(false); }

		inline QString name() const{ return this->metaObject()->className(); }

		inline int systemId() const { return mSystemId; }

		inline bool isInstalled() const{ return mInstalled; }

	protected:
		void setInstalled(bool installed){ mInstalled = installed; }

	private:
		bool mInstalled = false;
		int mSystemId = ST_NONE;
	};

}

#endif //ABSTRACTSYSTEM_H
