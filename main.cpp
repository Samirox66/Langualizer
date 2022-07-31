#include <QtWidgets/qapplication.h>
#include <QtWidgets/qwidget.h>
#pragma comment(lib, "Qt6Widgetsd.lib")

#include "App.h"

int main(int argc, char** argv)
{
	QApplication app(argc, argv);
	QWidget window;
	App application;
	
	window.setLayout(application.GetLayout());

	window.resize(800, 400);
	window.show();

	return app.exec();
}