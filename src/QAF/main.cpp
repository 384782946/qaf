#include "stdafx.h"
#include "qafapplication.h"

int main(int argc, char *argv[])
{
	QAFApplication app(argc, argv);

	if (!app.onlyOne())
		return 1;

	return app.run();
}
