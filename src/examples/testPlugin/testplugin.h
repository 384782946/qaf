#ifndef TESTPLUGIN_H
#define TESTPLUGIN_H

#include "testplugin_global.h"
#include "AbstractPlugin.h"

using namespace QAF;

class TESTPLUGIN_EXPORT testPluginFactory :public AbstractPluginFactory
{
public:
	virtual ObjectPtr<AbstractPlugin> create();
	virtual PluginType getType();
	virtual QString getVersion();
	virtual QString getDesc();
	virtual QString getAuthor();
	virtual bool isAutoLoad();
};

class  testPlugin:public AbstractPlugin
{
public:
	testPlugin();
	~testPlugin();

	virtual void install(const QMap<QString, QString>& params);
	virtual void uninstall();

private:

};

#endif // TESTPLUGIN_H