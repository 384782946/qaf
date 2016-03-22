#include "qafcore.h"
#include "ObjectSystem.h"
#include "PluginSystem.h"
#include "AbstractObject.h"
#include "ConfigSystem.h"
#include "UIInterface.h"
#include "QAFDirs.h"
#include "LogModel.h"

#include <QDockWidget>
#include <QTime>
#include <QDir>
#include <QDebug>

#include <stdio.h>
#include <stdlib.h>

void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
#ifndef QT_DEBUG //release�²����������Ϣ
	if(type == QtDebugMsg)
		return;
#endif

	QByteArray localMsg = msg.toLocal8Bit();
	switch (type) {
	case QtDebugMsg:
		fprintf(stderr, "Debug: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
		break;
	case QtInfoMsg:
		fprintf(stderr, "Info: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
		break;
	case QtWarningMsg:
		fprintf(stderr, "Warning: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
		break;
	case QtCriticalMsg:
		fprintf(stderr, "Critical: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
		break;
	case QtFatalMsg:
		fprintf(stderr, "Fatal: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
		abort();
	}

	if (QAFCorePtr)
	{
		QAF::LogModel* logModel = QAFCorePtr->getLogModel();
		if (logModel)
		{
			QString timeStr = QTime::currentTime().toString("hh:mm:ss");
			QAF::LogItem* item = new QAF::LogItem(type, timeStr, msg);
			logModel->addItem(item);
		}
	}
}

namespace QAF
{
	QAFCore::QAFCore()
		:mMessageCallback(NULL)
		, mUIInterface(NULL)
		, mLogModel(NULL)
	{
		mLogModel = new QAF::LogModel(this);
		mLogModel->setHeaders(QStringList() << LStr("����") << LStr("ʱ��") << LStr("����"));
	}

	QAFCore::~QAFCore()
	{
		foreach(int key, mSystems.keys()){
			AbstractSystem* system = mSystems.value(key, NULL);
			if (system){
				QString msg;
				if (key > ST_NONE && key < ST_CORE){
					msg = QString("%1%2").arg(LStr("����ж�غ���ģ�飺")).arg(system->name());
				} else if (key > ST_CORE){
					msg = QString("%1%2").arg(LStr("����ж����չģ�飺")).arg(system->name());
				}

				qDebug() << msg;
				system->uninstall();
			}
		}
		
		qDeleteAll(mSystems);

		//ȡ����Ϣ����
		qInstallMessageHandler(0);
	}

	void QAFCore::initialize(MessageCallback fun)
	{
		static bool init = false;
		if (!init)
		{
			init = true;
			qInstallMessageHandler(myMessageOutput);
			mMessageCallback = fun;
			if (mMessageCallback)
				(*mMessageCallback)(LStr("���ڳ�ʼ��..."));

			initCore(); //��ʼ�����Ĳ�
			initExtent(); //��ʼ����չ��
		}
	}

	void QAFCore::initCore()
	{
		addSystem(new ObjectSystem(ST_OBJECT,this));
		addSystem(new ConfigSystem(ST_CONFIG,this));

		foreach(int key, mSystems.keys()){
			if (key > ST_NONE && key < ST_CORE){
				AbstractSystem* system = mSystems.value(key, NULL);
				if (system){
					QString msg = QString("%1%2").arg(LStr("���ڼ��غ���ģ�飺")).arg(system->name());
					qDebug() << msg;
					if (mMessageCallback){
						(*mMessageCallback)(msg);
					}
					
					system->install();
				}
			}
		}
	}

	void QAFCore::initExtent()
	{
		addSystem(new PluginSystem(ST_PLUGIN,this));

		foreach(int key, mSystems.keys()){
			if (key > ST_CORE){
				AbstractSystem* system = mSystems.value(key, NULL);
				if (system){
					QString msg = QString("%1%2").arg(LStr("���ڼ�����չģ�飺")).arg(system->name());
					qDebug() << msg;
					if (mMessageCallback){
						(*mMessageCallback)(msg);
					}

					system->install();
				}
			}
		}
	}

	void QAFCore::addSystem(AbstractSystem* as)
	{
		if (!as)
			return;

		int id = as->systemId();
		if (!mSystems.contains(id))
		{
			mSystems.insert(id, as);
		}
	}

	void QAFCore::removeSystem(SystemType type)
	{
		if (mSystems.contains(type))
		{
			AbstractSystem* as = mSystems.take(type);
			if (as)
			{
				as->uninstall();
				delete as;
			}
		}
	}

	AbstractSystem* QAFCore::getSystem(int type) const
	{
		return mSystems.value(type, nullptr);
	}

	void QAFCore::setUIInterface(UIInterface* ui)
	{
		if (ui && !mUIInterface)
			mUIInterface = ui;
	}

	UIInterface* QAFCore::getUIInterface() const
	{
		return mUIInterface;
	}

	ConfigSystem* QAFCore::getConfigSystem() const
	{
		return static_cast<ConfigSystem*>(getSystem(ST_CONFIG));
	}

	ObjectSystem* QAFCore::getObjectSystem(int sysId) const
	{
		return static_cast<ObjectSystem*>(getSystem(sysId));
	}

	PluginSystem* QAFCore::getPluginSystem() const
	{
		return static_cast<PluginSystem*>(getSystem(ST_PLUGIN));
	}

	LogModel* QAFCore::getLogModel()
	{
		return mLogModel;
	}

}