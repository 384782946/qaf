#ifndef OBJECTMODEL_H
#define OBJECTMODEL_H

#include "AbstractTreeModel.h"


class ObjectModel : public AbstractTreeModel
{
	Q_OBJECT

public:
	ObjectModel(QObject *parent);
	~ObjectModel();

private:
	
};

#endif // OBJECTMODEL_H
