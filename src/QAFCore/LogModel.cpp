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
        if (role == Qt::DisplayRole || role == Qt::EditRole)
        {
            QString value;
			switch (index)
			{
                case 0:
                {
                    switch (mType) {
                    case QtDebugMsg:
                        value = LStr("调试");
                        break;
                    case QtInfoMsg:
                        value =  LStr("信息");
                        break;
                    case QtWarningMsg:
                        value =  LStr("警告");
                        break;
                    case QtCriticalMsg:
                        value =  LStr("危险");
                        break;
                    case QtFatalMsg:
                        value =  LStr("错误");
                        break;
                    default:
                        value =  "";
                        break;
                    }
                }
                break;
                case 1:
                    value = mTime;
                    break;
                case 2:
                    value = mContent;
                    break;
                default:
                    break;
			}

            return value;
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
