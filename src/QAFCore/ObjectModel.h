#ifndef OBJECTMODEL_H
#define OBJECTMODEL_H

#include "QtCommonModel.h"

namespace QAF
{
	class ObjectModel : public QtCommonModel
	{
		Q_OBJECT

	public:
		ObjectModel(QObject *parent);
		~ObjectModel();

	private:

	};
}

#endif // OBJECTMODEL_H
