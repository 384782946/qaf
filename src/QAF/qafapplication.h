#ifndef QAFAPPLICATION_H
#define QAFAPPLICATION_H

#include <QApplication>

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
	QSplashScreen* mSplashScreen = nullptr;
	QWidget* mMainWindow = nullptr;
};

#endif // QAFAPPLICATION_H
