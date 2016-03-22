#ifndef QAFAPPLICATION_H
#define QAFAPPLICATION_H

#include <QApplication>
#include <QtWidgets/QSplashScreen>

class QAFApplication : public QApplication
{
	Q_OBJECT

public:
	QAFApplication(int & argc, char ** argv);
	~QAFApplication();

	static void splashMessage(const QString&);

	void setSplashAlign(int align);
	void setSplashColor(const QColor&);
	QSplashScreen* splash();

	void startSplash();
	void finishSplash(QWidget* widget = NULL);

	void initialize();

private:
	static QAFApplication* sThis;

	QSplashScreen* mSplashScreen;
	int mSplashAlign;
	QColor mSplashColor;
};

#endif // QAFAPPLICATION_H
