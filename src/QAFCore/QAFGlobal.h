#ifndef QAFGLOBAL_H
#define QAFGLOBAL_H

#include <QString>
#include <Qt>

/************************************************************************/
/*   预处理                                                             */
/************************************************************************/
#define QAF_VERSON_1_0_0 0
#define QAF_VERSON_1_0_1 1

#define QAF_VERSION QAF_VERSON_1_0_0
#define QAF_VERSION_STR "1.0.0"

#define LStr(strings) QString::fromLocal8Bit(strings)

/************************************************************************/
/*   全局定义                                                           */
/************************************************************************/

namespace QAF
{
	enum SystemType
	{
		ST_NONE,
		ST_CONFIG,
		ST_OBJECT,
		ST_OBJECT_TEMP, //临时创建的对象系统，例如用于读取外部文件系统
		ST_LOG,
		ST_CORE = 100, //小于该值处于核心层，大于该值处于扩展层
		ST_PLUGIN,
		ST_CUSTOM = 256
	};

	enum PluginType //插件类型
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
		MI_CUSTOM = 256 //之后都是为用户自定义
	};

	enum ActionId
	{
		AI_RUNCONFIG,
		AI_CUSTOM = 256 //之后都是为用户自定义
	};

	enum WidgetId
	{
		WI_MAIN,
		WI_CUSTOM = 256 //之后都是为用户自定义
	};

	enum DockWidgetId
	{
		DI_PROJECT,
		DI_PROPERTY,
		DI_OBJECT,
		DI_CONSOLE,
		DI_CUSTOM = 256 //之后都是为用户自定义
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
		CT_NODE,
		CT_ATTR
	};
}

#endif //QAFGLOBAL_H
