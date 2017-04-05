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
					return LStr("����");
				case QtInfoMsg:
					return LStr("��Ϣ");
				case QtWarningMsg:
					return LStr("����");
				case QtCriticalMsg:
					return LStr("Σ��");
				case QtFatalMsg:
					return LStr("����");
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
