#include "QtWidgets/qapplication.h"
#include "QtWidgets/qwidget.h"
#include "QtWidgets/qboxlayout.h"
#include "Phrases.h"

#pragma comment(lib, "Qt6Widgetsd.lib")

int main(int argc, char** argv)
{
	QApplication app(argc, argv);
	QWidget window;
	Phrases phrases;
	QGridLayout* layout = new QGridLayout;
	layout->addWidget(phrases.GetWidget());
	window.setLayout(layout);

	window.resize(400, 200);
	window.show();

	return app.exec();
}