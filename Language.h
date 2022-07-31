#pragma once

#include <QtCore/qobject.h>
#include <QtCore/qstring.h>
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qtextedit.h>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qwidget.h>
#include <QtWidgets/qpushbutton.h>

#include <map>

class Language  : public QObject
{
	Q_OBJECT
public slots:
	void DeleteSlot();
	void ChangeEditability(bool);
signals:
	void DeleteSignal(const QString&);
public:
	Language(QString lang);
	QWidget* GetWidget();
	QString GetLanguage();
	std::string GetPhraseOutputString();
private:
	QString language;
	QLabel* langLabel;
	QTextEdit* textEdit;
	QVBoxLayout* layout;
	QPushButton* deleteBtn;
	QWidget* widget;
};
