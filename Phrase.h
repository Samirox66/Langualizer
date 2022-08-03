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
#include <sstream>

class Phrase : public QObject
{
	Q_OBJECT
public slots:
	void AddLangSlot(const QString& lang);
	void DeleteLangSlot(const QString& lang);
signals:

public:
	Phrase();
	Phrase(const std::string& phraseStr);
	void Init();
	QWidget* GetWidget();
	std::string GetPhraseOutputString();
private:
	QComboBox* addingLangBtn;
	QPushButton* editBtn;
	QPushButton* deleteBtn;
	QHBoxLayout* layout;
	QHBoxLayout* phraseLayout;
	QVBoxLayout* buttonsLayout;
	QWidget* phraseWidget;
	QWidget* buttonsWidget;
	QWidget* widget;
	QScrollArea* scrollArea;
	std::list<std::unique_ptr<Language>> pLanguages;
	std::map<QString, bool> langs;
};
