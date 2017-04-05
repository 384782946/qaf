#include "LogModel.h"
#include "QAFGlobal.h"
#include <QtGui/QColor>

namespace QAF
{
	LogModel::LogModel(QObject *parent)
		:QtCommonModel(parent)
	{

	}

	LogModel::~LogModel()
	{

	}

    QVariant LogItem::data(int index, int role) const
	{
		if (role == Qt::DisplayRole || role == Qt::EditRole){

			switch (index)
			{
			case 0:
			{
				switch (mType) {
				case QtDebugMsg:
					return LStr("调试");
				case QtInfoMsg:
					return LStr("信息");
				case QtWarningMsg:
					return LStr("警告");
				case QtCriticalMsg:
					return LStr("危险");
				case QtFatalMsg:
					return LStr("错误");
				default:
					return "";
				}
			}
			case 1:
				return mTime;
			case 2:
				return mContent;
			default:
				break;
			}
		}else if (role == Qt::TextColorRole){
			if (mType == QtWarningMsg || mType == QtCriticalMsg)
				return QColor(Qt::red);
			else
				return QVariant();
		}else if (role == Qt::DecorationRole){
		
		}else if (role == Qt::CheckStateRole){
			return QVariant();
		} else if (role == Qt::TextAlignmentRole){
			return int(Qt::AlignLeft | Qt::AlignVCenter);
		}

		return ModelItem::data(index, role);
	}
}
