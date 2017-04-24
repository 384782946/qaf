#include "PropertyEditerWidget.h"
#include <QVBoxLayout>
#include <QDateTime>

PropertyEditerWidget::PropertyEditerWidget(QWidget *parent)
	: QWidget(parent)
{
	mPropertyManager = new QtVariantPropertyManager(this);
	mPropertyBrowser = new QtTreePropertyBrowser(this);
    mPropertyBrowser->setFactoryForManager(mPropertyManager,new QtVariantEditorFactory(this));

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(mPropertyBrowser);
    setLayout(layout);

    QtVariantProperty* ppName = mPropertyManager->addProperty(QVariant::String, "name");
    ppName->setValue("zxj");
    ppName->setModified(true);
    mPropertyBrowser->addProperty(ppName);

    QtVariantProperty* ppTime = mPropertyManager->addProperty(QVariant::DateTime, "time");
    ppTime->setValue(QDateTime::currentDateTime());
    ppTime->setModified(true);
    mPropertyBrowser->addProperty(ppTime);
}

PropertyEditerWidget::~PropertyEditerWidget()
{

}
