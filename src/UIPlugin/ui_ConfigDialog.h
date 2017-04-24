/********************************************************************************
** Form generated from reading UI file 'ConfigDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONFIGDIALOG_H
#define UI_CONFIGDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_ConfigDialog
{
public:
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *lineEdit;
    QPushButton *pushButtonFilter;
    QVBoxLayout *verticalLayout;
    QTreeView *treeView;
    QLineEdit *lineEditPath;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButtonOK;
    QPushButton *pushButtonCancel;
    QPushButton *pushButtonApply;

    void setupUi(QDialog *ConfigDialog)
    {
        if (ConfigDialog->objectName().isEmpty())
            ConfigDialog->setObjectName(QStringLiteral("ConfigDialog"));
        ConfigDialog->resize(554, 469);
        verticalLayout_2 = new QVBoxLayout(ConfigDialog);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        lineEdit = new QLineEdit(ConfigDialog);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        horizontalLayout_2->addWidget(lineEdit);

        pushButtonFilter = new QPushButton(ConfigDialog);
        pushButtonFilter->setObjectName(QStringLiteral("pushButtonFilter"));

        horizontalLayout_2->addWidget(pushButtonFilter);


        verticalLayout_2->addLayout(horizontalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        treeView = new QTreeView(ConfigDialog);
        treeView->setObjectName(QStringLiteral("treeView"));

        verticalLayout->addWidget(treeView);


        verticalLayout_2->addLayout(verticalLayout);

        lineEditPath = new QLineEdit(ConfigDialog);
        lineEditPath->setObjectName(QStringLiteral("lineEditPath"));
        lineEditPath->setReadOnly(true);

        verticalLayout_2->addWidget(lineEditPath);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButtonOK = new QPushButton(ConfigDialog);
        pushButtonOK->setObjectName(QStringLiteral("pushButtonOK"));

        horizontalLayout->addWidget(pushButtonOK);

        pushButtonCancel = new QPushButton(ConfigDialog);
        pushButtonCancel->setObjectName(QStringLiteral("pushButtonCancel"));

        horizontalLayout->addWidget(pushButtonCancel);

        pushButtonApply = new QPushButton(ConfigDialog);
        pushButtonApply->setObjectName(QStringLiteral("pushButtonApply"));

        horizontalLayout->addWidget(pushButtonApply);


        verticalLayout_2->addLayout(horizontalLayout);


        retranslateUi(ConfigDialog);
        QObject::connect(pushButtonOK, SIGNAL(clicked()), ConfigDialog, SLOT(accept()));
        QObject::connect(pushButtonCancel, SIGNAL(clicked()), ConfigDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(ConfigDialog);
    } // setupUi

    void retranslateUi(QDialog *ConfigDialog)
    {
        ConfigDialog->setWindowTitle(QApplication::translate("ConfigDialog", "\350\277\220\350\241\214\351\205\215\347\275\256", 0));
        lineEdit->setPlaceholderText(QApplication::translate("ConfigDialog", "\350\257\267\350\276\223\345\205\245\345\205\263\351\224\256\345\255\227...", 0));
        pushButtonFilter->setText(QApplication::translate("ConfigDialog", "\346\237\245\350\257\242", 0));
        pushButtonOK->setText(QApplication::translate("ConfigDialog", "\347\241\256\345\256\232", 0));
        pushButtonCancel->setText(QApplication::translate("ConfigDialog", "\345\217\226\346\266\210", 0));
        pushButtonApply->setText(QApplication::translate("ConfigDialog", "\345\272\224\347\224\250", 0));
    } // retranslateUi

};

namespace Ui {
    class ConfigDialog: public Ui_ConfigDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONFIGDIALOG_H
