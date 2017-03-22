#ifndef PROPERTYEDITERWIDGET_H
#define PROPERTYEDITERWIDGET_H

#include <QWidget>
#include "qttreepropertybrowser.h"
#include "qtvariantproperty.h"

class PropertyEditerWidget : public QWidget
{
	Q_OBJECT

public:
	PropertyEditerWidget(QWidget *parent = 0);
	~PropertyEditerWidget();

private:
	QtTreePropertyBrowser* mPropertyBrowser;
	QtVariantPropertyManager* mPropertyManager;
};

#endif // PROPERTYEDITERWIDGET_H
