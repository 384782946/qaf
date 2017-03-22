/*!
 * \file LogModel.h
 * \date 2016/01/16 14:34
 *
 * \author zxj
 * Contact: user@company.com
 *
 * \brief 
 *
 * 日志模型，基于AbstractTreeModel
 *
 * \note
*/

#ifndef LOGMODEL_H
#define LOGMODEL_H

#include "QtCommonModel.h"
#include "ModelItem.h"

namespace QAF
{
    class LogItem;
    typedef QSharedPointer<LogItem> LogItemPtr;

	class LogItem :public ModelItem
	{
	public:
		LogItem(int type,QString time,QString content)
			:mType(type), mTime(time), mContent(content)
		{
		}

        virtual QString className() const {return "LogItem";}
		virtual QVariant data(int index, int role = Qt::DisplayRole);

	private:
		int mType;
		QString mTime;
		QString mContent;
	};

	class LogModel :
		public QtCommonModel
	{
	public:
		LogModel(QObject *parent = nullptr);
		~LogModel();
	};
}

#endif //LOGMODEL_H
