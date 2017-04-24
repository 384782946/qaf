#ifndef QAF_H
#define QAF_H

#include <QtWidgets/QMainWindow>
#include "UIInterface.h"
#include "ui_mainwindow.h"

using QAF::UIInterface;

class MainWindow
	: public QMainWindow
	, public UIInterface
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = 0);
	~MainWindow();

    virtual QWidget* getMainWindow();
    virtual QMenu* getMenu(int id);
    virtual QAction* getAction(int id);
    virtual QWidget* getWidget(int id);
    virtual QDockWidget* getDockWidget(int id);
    virtual void setMenu(int id, QMenu* menu);
    virtual void setAction(int id, QAction* action);
    virtual void setWidget(int id, QWidget* widget);
    virtual void setDockWidget(int id, QDockWidget* dock, QAF::DockWidgetPos pos = QAF::DWP_BOTTOM);

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
