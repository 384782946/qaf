#pragma once

#include "QAFGlobal.h"

class QMenu;
class QAction;
class QWidget;
class QDockWidget;
class QSplashScreen;

namespace QAF
{
	class UIInterface
	{
	public:
		UIInterface(){}
		virtual ~UIInterface(){}

		virtual QMenu* getMenu(int id) = 0;

		virtual QAction* getAction(int id) = 0;

		virtual QWidget* getWidget(int id) = 0;

		virtual QDockWidget* getDockWidget(int id) = 0;

		virtual QWidget* getMainWindow() = 0;

		virtual void setMenu(int id, QMenu* menu) = 0;

		virtual void setAction(int id, QAction* action) = 0;

		virtual void setWidget(int id, QWidget* widget) = 0;

		virtual void setDockWidget(int id, QDockWidget* dock, DockWidgetPos pos = DWP_BOTTOM) = 0;
	};
}
