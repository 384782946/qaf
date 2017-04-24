/*!
 * \file QAFContext.h
 * \date 2016/07/22
 *
 * \author zxj
 *
 * \brief 
 *
 * agent of the core model,to control user's access authority
 *
 * \note
*/

#ifndef QAFCONTEXT_H
#define QAFCONTEXT_H

#include "qafcore_global.h"
#include "Singleton.h"
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

		/*!
		 * \fn	wellKnwonPath
		 * \brief 
		 *		To get common path in this application
		 * \param 
		 *		dt:the type of dir
		 * \return
		 *      absolute path for given type
		 */
		static QString wellKnownPath(DirType);

		/*!
		 * \fn	getLogModel
		 * \brief 
		 *		get log model
		 * \param 
		 *		void
		 * \return
		 *		pointer of log model
		 */
		LogModel* getLogModel() const;

		/*!
		 * \fn	setUIInterface
		 * \brief
		 * \param 
		 *		
		 * \return
		 *		void
		 */
		void setUIInterface(UIInterface*);

		/*!
		* \fn	getUIInterface
		* \brief 
		*		get the interface of GUI to create your custom appearance
		* \param 
		*		void
		* \return
		*		pointer of ui interface
		*/
		UIInterface* getUIInterface() const;

		/*!
		* \fn	getSystem
		* \brief 
		*		get system
		* \param 
		*		st:system type what your what
		* \return
		*		pointer of abstract system
		*/
		AbstractSystem* getSystem(SystemType) const;
	};
}

#endif //QAFCONTEXT_H
