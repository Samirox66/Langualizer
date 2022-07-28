#pragma once
#include "qobject.h"
#include "qstring.h"
#include "QtWidgets/qboxlayout.h"
#include "QtWidgets/qpushbutton.h"
#include "QtWidgets/qcombobox.h"

#include "Phrase.h"

#include <list>
#include <map>
#include <algorithm>

class Phrases : public QObject
{
	Q_OBJECT
public slots:
	void AddLangSlot(const QString& lang);
	void DeleteLangSlot(const QString& lang);
signals:

public:
	Phrases();
	QWidget* GetWidget();
private:
	QComboBox* addingLangButton;
	QHBoxLayout* layout;
	QWidget* widget;
	std::list<std::unique_ptr<Phrase>> phrases;
	std::map<QString, std::pair<int, bool>> langs;
};

