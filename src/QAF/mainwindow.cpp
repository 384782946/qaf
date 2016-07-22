#include "stdafx.h"
#include "mainwindow.h"
#include <QAFGlobal.h>
#include <QAFContext.h>
#include "qafapplication.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	ui.mainToolBar->setWindowTitle(LStr("������"));

	//����Ƕ�봰�����ȼ�
	setCorner(Qt::TopLeftCorner, Qt::LeftDockWidgetArea);
	setCorner(Qt::BottomLeftCorner, Qt::LeftDockWidgetArea);
	setCorner(Qt::TopRightCorner, Qt::RightDockWidgetArea);
	setCorner(Qt::BottomRightCorner, Qt::RightDockWidgetArea);

	QAFApplication::splashMessage(LStr("���ڳ�ʼ������..."));
	QAFApplication::splashMessage(LStr("���ڴ����˵�..."));
	createMenu();
	createAction();

	QAF::QAFContext::getSingleton()->setUIInterface(this);
}

MainWindow::~MainWindow()
{

}

void MainWindow::createMenu()
{
	setMenu(QAF::MI_FILE, ui.menuFile);
	setMenu(QAF::MI_EDIT, ui.menuEdit);
	setMenu(QAF::MI_VIEW, ui.menuView);
	setMenu(QAF::MI_ACTION, ui.menuAction);
	setMenu(QAF::MI_SETTING, ui.menuSetting);
	setMenu(QAF::MI_HELP, ui.menuHelp);
}

void MainWindow::createAction()
{
	
	QAction* as = ui.menuSetting->addAction(QIcon(":/QAF/Resources/gear.png"),LStr("��������"));

	setAction(QAF::AI_RUNCONFIG,as);

	ui.mainToolBar->addAction(as);
}

QWidget* MainWindow::getMainWindow()
{
	return this;
}

QMenu* MainWindow::getMenu(int id)
{
	return mMenus.value(id, nullptr);
}

QAction* MainWindow::getAction(int id)
{
	return mActions.value(id, nullptr);
}

QWidget* MainWindow::getWidget(int id)
{
	return mWidgets.value(id, nullptr);
}

QDockWidget* MainWindow::getDockWidget(int id)
{
	return mDockWidgets.value(id, nullptr);
}

void MainWindow::setMenu(int id, QMenu* menu)
{
	if (menu && !mMenus.contains(id))
	{
		mMenus.insert(id, menu);
	}
}

void MainWindow::setAction(int id, QAction* action)
{
	if (action && !mActions.contains(id))
	{
		mActions.insert(id, action);
	}
}

void MainWindow::setWidget(int id, QWidget* widget)
{
	if (widget && !mWidgets.contains(id))
	{
		mWidgets.insert(id, widget);
	}
}

void MainWindow::setDockWidget(int id, QDockWidget* dock, QAF::DockWidgetPos pos/* = QAF::DWP_AUTO*/)
{
	if (dock && !mDockWidgets.contains(id))
	{
		//Ѱ�Ҿ�����ͬ����λ�õ�dock
		dock->setProperty("dockPos", (int)pos);
		QDockWidget* lastDock = nullptr;
		foreach(QDockWidget* widget, mDockWidgets){
			if (widget && widget->property("dockPos").toInt() == pos){
				lastDock = widget;
			}
		}

		this->addDockWidget((Qt::DockWidgetArea)pos, dock);
		QAction* toggle = dock->toggleViewAction();
		getMenu(QAF::MI_VIEW)->addAction(toggle);
		mDockWidgets.insert(id, dock);

		if (lastDock){
			this->tabifyDockWidget(lastDock, dock);
		}
	}
}