#include "testplugin.h"
#include <QDockWidget>
#include <QMenu>
#include <UIInterface.h>
#include <QAFContext.h>
#include <ObjectSystem.h>
#include "TestUI.h"

ObjectPtr<AbstractPlugin> testPluginFactory::create()
{
	QWidget* widget = new TestUI();
	QDockWidget* dock = new QDockWidget(LStr("测试插件"));
	dock->setWidget(widget);
	QAFContext::getSingleton()->getUIInterface()->setDockWidget(DI_CUSTOM + 1, dock, QAF::DWP_LEFT);
	QAFContext::getSingleton()->getUIInterface()->getMenu(QAF::MI_ACTION)->addAction(LStr("测试插件动作"));
	return static_cast<ObjectSystem*>(QAFContext::getSingleton()->getSystem(ST_OBJECT))->create<testPlugin>();
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

void testPlugin::install(const QMap<QString, QString>& params)
{

}

void testPlugin::uninstall()
{

}

extern "C"  TESTPLUGIN_EXPORT AbstractPluginFactory*  create()
{
	return new testPluginFactory();
}