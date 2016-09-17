#ifndef OBJECTMODEL_H
#define OBJECTMODEL_H

#include "CommonTreeModel.h"

namespace QAF
{
	class ObjectModel : public CommonTreeModel
	{
		Q_OBJECT

	public:
		ObjectModel(QObject *parent);
		~ObjectModel();

	private:

	};
}

#endif // OBJECTMODEL_H
