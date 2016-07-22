/*!
 * \file Context.h
 * \date 2016/07/21 22:44
 *
 * \author zxj
 * Contact: user@company.com
 *
 * \brief 
 *
 * the agent of core model,to control user's access authority
 *
 * \note
*/

#pragma once

#include <Singleton.h>
#include "qafcore_global.h"
#include "QAFGlobal.h"

namespace QAF
{
	class UIInterface;
	class AbstractSystem;
	class LogModel;

	class QAFCORE_EXPORT QAFContext:public Singleton<QAFContext>
	{
	public:
		void construct();
		void destruct();

		LogModel* getLogModel() const;

		void setUIInterface(UIInterface*);
		UIInterface* getUIInterface() const;

		AbstractSystem* getSystem(SystemType) const;
	};
}
