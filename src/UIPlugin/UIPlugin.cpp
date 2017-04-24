#include "UIPlugin.h"
#include <QDockWidget>
#include <QMenu>
#include <QAFContext.h>
#include <ObjectSystem.h>
#include <UIInterface.h>
#include "ConsoleWidget.h"
#include "ConfigDialog.h"
#include "PropertyEditerWidget.h"

UIInterface* g_UIInterface = nullptr;

ObjectPtr<AbstractPlugin> UIPluginFactory::create()
{
	g_UIInterface = QAFContext::getSingleton()->getUIInterface();
	return static_cast<ObjectSystem*>(QAFContext::getSingleton()->getSystem(ST_OBJECT))->create<UIPlugin>();
}

QAF::PluginType UIPluginFactory::getType()
{
	return PT_GUI;
}

QString UIPluginFactory::getVersion()
{
	return "1.0";
}

QString UIPluginFactory::getDesc()
{
	return "UI plugins";
}

QString UIPluginFactory::getAuthor()
{
	return "zxj";
}

bool UIPluginFactory::isAutoLoad()
{
	return true;
}

//////////////////////////////////////////////////////////////////////////

UIPlugin::UIPlugin()
{

}

UIPlugin::~UIPlugin()
{

}

void UIPlugin::install(const QMap<QString, QString>&)
{
    QDockWidget* consoleDock = new QDockWidget(LStr("控制台"));
	consoleDock->setWidget(new ConsoleWidget(consoleDock));
	g_UIInterface->setDockWidget(DI_CONSOLE, consoleDock, DWP_BOTTOM);

    QDockWidget* propertyDock = new QDockWidget(LStr("属性编辑器"));
	propertyDock->setWidget(new PropertyEditerWidget(propertyDock));
	g_UIInterface->setDockWidget(DI_PROPERTY, propertyDock, DWP_RIGHT);

	ConfigDialog* confDlg = new ConfigDialog(g_UIInterface->getMainWindow());
	QAction* act = g_UIInterface->getAction(AI_RUNCONFIG);
	connect(act, SIGNAL(triggered(bool)), confDlg, SLOT(show()));
}

void UIPlugin::uninstall()
{

}

extern "C"  UIPLUGIN_EXPORT AbstractPluginFactory*  create()
{
	return new UIPluginFactory();
}
