#include "PropertyEditerWidget.h"
#include <QVBoxLayout>

PropertyEditerWidget::PropertyEditerWidget(QWidget *parent)
	: QWidget(parent)
{
	mPropertyManager = new QtVariantPropertyManager(this);
	mPropertyBrowser = new QtTreePropertyBrowser(this);
	QtVariantProperty* property = mPropertyManager->addProperty(QVariant::String, "name");
	property->setValue("zxj");
	mPropertyBrowser->addProperty(property);
	QVBoxLayout* layout = new QVBoxLayout(this);
	layout->addWidget(mPropertyBrowser);
	setLayout(layout);
}

PropertyEditerWidget::~PropertyEditerWidget()
{

}
