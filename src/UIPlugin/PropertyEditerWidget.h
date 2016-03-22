#ifndef PROPERTYEDITERWIDGET_H
#define PROPERTYEDITERWIDGET_H

#include <QWidget>
#include "QtPropertyBrowser/qttreepropertybrowser.h"
#include "QtPropertyBrowser/qtvariantproperty.h"

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
