/********************************************************************************
** Form generated from reading UI file 'TestUI.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TESTUI_H
#define UI_TESTUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TestUI
{
public:
    QVBoxLayout *verticalLayout;
    QTextEdit *textEdit;

    void setupUi(QWidget *TestUI)
    {
        if (TestUI->objectName().isEmpty())
            TestUI->setObjectName(QStringLiteral("TestUI"));
        TestUI->resize(553, 407);
        verticalLayout = new QVBoxLayout(TestUI);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        textEdit = new QTextEdit(TestUI);
        textEdit->setObjectName(QStringLiteral("textEdit"));

        verticalLayout->addWidget(textEdit);


        retranslateUi(TestUI);

        QMetaObject::connectSlotsByName(TestUI);
    } // setupUi

    void retranslateUi(QWidget *TestUI)
    {
        TestUI->setWindowTitle(QApplication::translate("TestUI", "TestUI", 0));
        textEdit->setHtml(QApplication::translate("TestUI", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:36pt; font-weight:600; vertical-align:super;\">\345\244\247\345\256\266\345\245\275,</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:18pt; font-weight:600; color:#ff0000; vertical-align:super;\">\350\277\231\351\207\214\346\230\257\346\217\222\344\273\266\346\265\213\350\257\225\347\252\227\345\217\243</span></p>\n"
"<p dir='rtl' style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; te"
                        "xt-indent:0px;\"><span style=\" font-size:18pt; font-weight:600; color:#ff0000; vertical-align:super;\">\346\210\221\346\230\257\351\235\240\345\217\263\347\232\204\346\226\207\346\234\254</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><a href=\"www.baidu.com\"><span style=\" font-size:10pt; text-decoration: underline; color:#0000ff;\">\347\231\276\345\272\246\344\270\200\344\270\213</span></a></p></body></html>", 0));
    } // retranslateUi

};

namespace Ui {
    class TestUI: public Ui_TestUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TESTUI_H
