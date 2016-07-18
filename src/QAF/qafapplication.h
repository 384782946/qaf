#ifndef QAFAPPLICATION_H
#define QAFAPPLICATION_H

#include <QApplication>

class QAFApplication : public QApplication
{
	Q_OBJECT

public:
	QAFApplication(int & argc, char ** argv);
	~QAFApplication();

	static void splashMessage(const QString&);

	int run();

	bool onlyOne();

protected:
	void initialize();

private:
	QSplashScreen* mSplashScreen = nullptr;
	QWidget* mMainWindow = nullptr;
};

#endif // QAFAPPLICATION_H
