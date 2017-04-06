#ifndef QAFAPPLICATION_H
#define QAFAPPLICATION_H

#include <QApplication>

class QSplashScreen;

class QAFApplication : public QApplication
{
public:
	QAFApplication(int & argc, char ** argv);
	~QAFApplication();

	int run();

	bool onlyOne();

	static void splashMessage(QString);

protected:
	void initialize();

private:
    QSplashScreen* mSplashScreen;
    QWidget* mMainWindow;
};

#endif // QAFAPPLICATION_H
