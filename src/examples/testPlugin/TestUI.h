#ifndef TESTUI_H
#define TESTUI_H

#include <QWidget>
#include "ui_TestUI.h"

class TestUI : public QWidget
{
	Q_OBJECT

public:
	TestUI(QWidget *parent = 0);
	~TestUI();

private:
	Ui::TestUI ui;
};

#endif // TESTUI_H
