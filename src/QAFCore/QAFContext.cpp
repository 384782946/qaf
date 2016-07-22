#include "QAFContext.h"
#include "QAFCore.h"


namespace QAF
{
	void QAFContext::setUIInterface(UIInterface* ui)
	{
		if (ui){
			QAFCore::getSingleton()->setUIInterface(ui);
		}
	}

	UIInterface* QAFContext::getUIInterface() const
	{
		return QAFCore::getSingleton()->getUIInterface();
	}

	AbstractSystem* QAFContext::getSystem(SystemType st) const
	{
		return QAFCore::getSingleton()->getSystem(st);
	}

	void QAFContext::construct()
	{
		QAFCore::getSingleton()->initialize();
	}

	void QAFContext::destruct()
	{
		QAFCore::release();
	}

	LogModel* QAFContext::getLogModel() const
	{
		return QAFCore::getSingleton()->getLogModel();
	}

}