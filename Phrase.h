#pragma once
#include <QtCore/qobject.h>
#include <QtCore/qstring.h>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qcombobox.h>
#include <QtWidgets/qscrollarea.h>

#include "Language.h"

#include <list>
#include <map>
#include <algorithm>

class Phrase : public QObject
{
	Q_OBJECT
public slots:
	void AddLangSlot(const QString& lang);
	void DeleteLangSlot(const QString& lang);
signals:

public:
	Phrase();
	QWidget* GetWidget();
	std::string GetPhraseOutputString();
private:
	QComboBox* addingLangBtn;
	QPushButton* editBtn;
	QHBoxLayout* layout;
	QHBoxLayout* phraseLayout;
	QWidget* phraseWidget;
	QWidget* widget;
	QScrollArea* scrollArea;
	std::list<std::unique_ptr<Language>> pLanguages;
	std::map<QString, bool> langs;
};

