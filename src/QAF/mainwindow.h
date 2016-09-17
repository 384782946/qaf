#ifndef QAF_H
#define QAF_H

#include <QtWidgets/QMainWindow>
#include "UIInterface.h"
#include "ui_mainwindow.h"

using QAF::UIInterface;

class MainWindow 
	: public QMainWindow
	,public UIInterface
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = 0);
	~MainWindow();

	inline virtual QWidget* getMainWindow();
	inline virtual QMenu* getMenu(int id);
	inline virtual QAction* getAction(int id);
	inline virtual QWidget* getWidget(int id);
	inline virtual QDockWidget* getDockWidget(int id);
	inline virtual void setMenu(int id, QMenu* menu);
	inline virtual void setAction(int id, QAction* action);
	inline virtual void setWidget(int id, QWidget* widget);
	inline virtual void setDockWidget(int id, QDockWidget* dock, QAF::DockWidgetPos pos = QAF::DWP_BOTTOM);

protected:
	void createMenu();
	void createAction();

private:
	Ui::MainWindow ui;

	QSplashScreen* mSplashScreen;
	QMap<int, QMenu*> mMenus;
	QMap<int, QAction*> mActions;
	QMap<int, QWidget*> mWidgets;
	QMap<int, QDockWidget*> mDockWidgets;
};

#endif // QAF_H
