#pragma once
#include <QtCore/qobject.h>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qwidget.h>
#include <QtCore/qstring.h>
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qscrollarea.h>

#include "Phrase.h"

#include <vector>

class Phrases : public QObject
{
	Q_OBJECT
public slots:
	void AddPhraseSlot();
	signals:
public:
	Phrases(const QString& deck);
	QWidget* GetWidget();
	std::string GetPhraseOutputString();
private:
	QPushButton* addPhraseBtn;
	QLabel* deckLabel;
	QWidget* widget;
	QWidget* phrasesWidget;
	QVBoxLayout* layout;
	QVBoxLayout* phrasesLayout;
	QScrollArea* scrollArea;
	const QString deckName;
	std::vector<std::unique_ptr<Phrase>> phrases;
};

