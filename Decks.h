#pragma once
#include <QtCore/qobject.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qwidget.h>
#include <QtWidgets/qscrollarea.h>
#include <QtWidgets/qlineedit.h>

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
	void AddDeckSlot();
signals:
	
public:
	Decks(class App& app);
	QWidget* GetWidget();
	void ReadDecks();
private:
	QScrollArea* scrollArea;
	QWidget* scrollWidget;
	QWidget* widget;
	QVBoxLayout* layout;
	QVBoxLayout* scrollLayout;
	QPushButton* addDeckBtn;
	QLineEdit* newDeckEdit;
	class App* pApp;
	std::vector<std::unique_ptr<DeckPushButton>> decks;
};

