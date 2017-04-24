#ifndef CONSOLEWIDGET_H
#define CONSOLEWIDGET_H

#include <QWidget>
#include "ui_ConsoleWidget.h"

class QSortFilterProxyModel;

class ConsoleWidget : public QWidget
{
	Q_OBJECT

public:
	ConsoleWidget(QWidget *parent = 0);
	~ConsoleWidget();

private slots:
	void on_comboBox_currentIndexChanged(int type);

private:
	Ui::ConsoleWidget ui;

	QSortFilterProxyModel* mModel;
};

#endif // CONSOLEWIDGET_H
