#pragma once
#include <QtCore/qobject.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qwidget.h>
#include <QtWidgets/qscrollarea.h>

#include <vector>

class DeckPushButton : public QPushButton
{
	Q_OBJECT
public slots:
	void DeckClickSlot();
signals:
	void DeckClickSignal(const QString&);
public:
	DeckPushButton(const QString& text);
private:

};

class Decks : public QObject
{
	Q_OBJECT
public slots:
	
signals:
	
public:
	Decks(class App& app);
	QScrollArea* GetWidget();
private:
	QScrollArea* scrollArea;
	QWidget* widget;
	QVBoxLayout* layout;
	std::vector<std::unique_ptr<DeckPushButton>> decks;
};

