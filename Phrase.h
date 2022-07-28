#pragma once

#include "qobject.h"
#include "QtCore/qstring.h"
#include "QtWidgets/qlabel.h"
#include "QtWidgets/qtextedit.h"
#include "QtWidgets/qboxlayout.h"
#include "QtWidgets/qwidget.h"
#include "QtWidgets/qpushbutton.h"

#include <map>

class Phrase  : public QObject
{
	Q_OBJECT
public slots:
	void DeleteSlot();
signals:
	void DeleteSignal(const QString&);
public:
	Phrase(QString lang);
	QWidget* GetWidget();
	QString GetLanguage();
private:
	QString language;
	QLabel* langLabel;
	QTextEdit* textEdit;
	QVBoxLayout* layout;
	QPushButton* deleteBtn;
	QWidget* widget;
};
