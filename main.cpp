#include <QtWidgets/qapplication.h>
#include <QtWidgets/qlabel.h>
#pragma comment(lib, "Qt6Widgetsd.lib")

int main(int argc, char** argv) {
	QApplication app(argc, argv);
	QLabel lab("start");
	lab.resize(200, 50);
	lab.show();

	return app.exec();
}