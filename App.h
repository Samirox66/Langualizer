#pragma once

#include <QtWidgets/qapplication.h>
#include <QtWidgets/qwidget.h>
#include <QtWidgets/qboxlayout.h>
#include <QtCore/qobject.h>

#include "Decks.h"
#include "Phrases.h"

#include <map>
#include <fstream>
#include <string>

class App : public QObject
{
	Q_OBJECT
public slots:
	void ReadDeck(const QString& deckName);
signals:

public:
	App();
	QGridLayout* GetLayout();
	~App();
	void WritePhrases();
private:
	QGridLayout* layout;
	Decks decks;
	std::map<QString, std::unique_ptr<Phrases>> decksMap;
	QString currentDeck;
};
