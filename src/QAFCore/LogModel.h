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

#pragma once
#include "QtCommonModel.h"
#include "ModelItem.h"

namespace QAF
{
	class LogItem :public ModelItem
	{
	public:
		LogItem(int type,QString time,QString content)
			:mType(type), mTime(time), mContent(content)
		{
		}

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