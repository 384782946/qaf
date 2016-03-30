#include "UIPlugin.h"
#include "QAFCore.h"
#include "ObjectSystem.h"
#include <QDockWidget>
#include "UIInterface.h"
#include "ConsoleWidget.h"
#include "ConfigDialog.h"
#include "PropertyEditerWidget.h"

#include <QMenu>

QAFCore* g_QAFCore = nullptr;

ObjectPtr<AbstractPlugin> UIPluginFactory::create(QAFCore* core)
{
	g_QAFCore = core;
	return QAFCorePtr->getObjectSystem()->create<UIPlugin>();
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

void UIPlugin::install()
{
	if (isInstalled())
		return;

	QDockWidget* consoleDock = new QDockWidget(LStr("控制台"));
	consoleDock->setWidget(new ConsoleWidget(consoleDock));
	g_QAFCore->getUIInterface()->setDockWidget(DI_CONSOLE, consoleDock, DWP_BOTTOM);

	QDockWidget* propertyDock = new QDockWidget(LStr("属性编辑器"));
	propertyDock->setWidget(new PropertyEditerWidget(propertyDock));
	g_QAFCore->getUIInterface()->setDockWidget(DI_PROPERTY, propertyDock, DWP_RIGHT);

	ConfigDialog* confDlg = new ConfigDialog(g_QAFCore->getUIInterface()->getMainWindow());
	QAction* act = g_QAFCore->getUIInterface()->getAction(AI_RUNCONFIG);
	connect(act, SIGNAL(triggered(bool)), confDlg, SLOT(show()));

	setInstalled(false);
	// 	QWidget* widget = new TestUI();
	// 	QDockWidget* dock = new QDockWidget(LStr("测试插件"));
	// 	dock->setWidget(widget);
	// 	core->getUIInterface()->setDockWidget(DI_CUSTOM+1, dock,QAF::DWP_BOTTOM);
	// 	core->getUIInterface()->getMenu(QAF::MI_ACTION)->addAction(LStr("测试插件动作"));
}

void UIPlugin::uninstall()
{

}

extern "C"  UIPLUGIN_EXPORT AbstractPluginFactory*  create()
{
	return new UIPluginFactory();
}