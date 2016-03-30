#pragma once

#include "qafcore_global.h"

#include <QString>
#include <Qt>

/************************************************************************/
/*   Ԥ����                                                             */
/************************************************************************/
#define _VERSON_0_0 0
#define _VERSON_0_1 1

#define QAF_VERSION _VERSON_0_0
#define QAF_VERSION_STR "v0.0"

#define QAFCorePtr QAF::QAFCore::getSingleton()
#define LStr(strings) QString::fromLocal8Bit(strings)

template<typename T1,typename T2>
class CanConvert
{
	typedef char Type1[1];
	typedef char Type2[2];

	static Type1& test(T2&);
	static Type2& test(...);
	static T1& make();

public:
	enum { ret = (sizeof(test(make())) == sizeof(Type1)) };
};

template<typename T1,typename T2>
class IsSameType
{
public:
	enum {ret = false};
};

template<typename T>
class IsSameType<T,T>
{
public:
	enum { ret = true };
};

#define ASSERT_SAME_TYPE(classname1,classname2) static_assert(IsSameType<classname1,classname2>::ret, #classname1##" is not the same type with "###classname2)
#define ASSERT_CONVERTIBLE_TYPE(classname1,classname2) static_assert(CanConvert<classname1,classname2>::ret,#classname1##" can not convert to "###classname2)

/************************************************************************/
/*   ȫ�ֶ���                                                           */
/************************************************************************/

namespace QAF
{
	enum SystemType
	{
		ST_NONE,
		ST_CONFIG,
		ST_OBJECT,
		ST_OBJECT_TEMP, //��ʱ�����Ķ���ϵͳ���������ڶ�ȡ�ⲿ�ļ�ϵͳ
		ST_LOG,
		ST_CORE = 100, //С�ڸ�ֵ���ں��Ĳ㣬���ڸ�ֵ������չ��
		ST_PLUGIN,
		ST_CUSTOM = 256
	};

	enum PluginType //�������
	{
		PT_NONE,
		PT_GUI,
		PT_SERVER
	};

	enum PluginMenuType
	{
		PMT_NONE,
		PMT_TOPLEVEL,
		PMT_NORMAL
	};

	enum DirType
	{
		DT_HOME,
		DT_CONFIG,
		DT_TRANSTOR,
		DT_LOG,
		DT_DATA,
		DT_PLUGIN
	};

	enum MenuId
	{
		MI_FILE,
		MI_EDIT,
		MI_VIEW,
		MI_ACTION,
		MI_SETTING,
		MI_HELP,
		MI_CUSTOM = 256 //֮����Ϊ�û��Զ���
	};

	enum ActionId
	{
		AI_RUNCONFIG,
		AI_CUSTOM = 256 //֮����Ϊ�û��Զ���
	};

	enum WidgetId
	{
		WI_MAIN,
		WI_CUSTOM = 256 //֮����Ϊ�û��Զ���
	};

	enum DockWidgetId
	{
		DI_PROJECT,
		DI_PROPERTY,
		DI_OBJECT,
		DI_CONSOLE,
		DI_CUSTOM = 256 //֮����Ϊ�û��Զ���
	};

	enum DockWidgetPos
	{
		DWP_LEFT = Qt::LeftDockWidgetArea,
		DWP_RIGHT = Qt::RightDockWidgetArea,
		DWP_TOP = Qt::TopDockWidgetArea,
		DWP_BOTTOM = Qt::BottomDockWidgetArea,
		DWP_None = Qt::NoOpaqueDetection
	};

	enum ConfigDataRole
	{
		CDR_TYPE = Qt::UserRole,
		CDR_ACTIVE,
		CDR_OPTIONS,
		CDT_NOTIFY,
		CDR_REGX
	};

	enum ConfigType
	{
		CT_GROUP,
		CT_ITEM
	};
}