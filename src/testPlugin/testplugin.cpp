#include "testplugin.h"
#include "QAFCore.h"
#include "ObjectSystem.h"
#include "TestUI.h"
#include <QDockWidget>
#include "UIInterface.h"

#include <QMenu>

ObjectPtr<AbstractPlugin> testPluginFactory::create(QAFCore* core)
{
	QWidget* widget = new TestUI();
	QDockWidget* dock = new QDockWidget(LStr("测试插件"));
	dock->setWidget(widget);
	core->getUIInterface()->setDockWidget(DI_CUSTOM+1, dock,QAF::DWP_LEFT);
	core->getUIInterface()->getMenu(QAF::MI_ACTION)->addAction(LStr("测试插件动作"));
	return QAFCorePtr->getObjectSystem()->create<testPlugin>();
}

QAF::PluginType testPluginFactory::getType()
{
	return PT_GUI;
}

QString testPluginFactory::getVersion()
{
	return "1.0";
}

QString testPluginFactory::getDesc()
{
	return "test for plugin";
}

QString testPluginFactory::getAuthor()
{
	return "zxj";
}

bool testPluginFactory::isAutoLoad()
{
	return true;
}

testPlugin::testPlugin()
{

}

testPlugin::~testPlugin()
{

}

void testPlugin::install()
{

}

void testPlugin::uninstall()
{

}

extern "C"  TESTPLUGIN_EXPORT AbstractPluginFactory*  create()
{
	return new testPluginFactory();
}