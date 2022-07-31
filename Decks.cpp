#include "Decks.h"
#include "App.h"

Decks::Decks(App& app)
{
	layout = new QVBoxLayout;
	widget = new QWidget;
	scrollArea = new QScrollArea;
	scrollArea->setMaximumWidth(170);
	scrollArea->setWidgetResizable(true);
	decks.push_back(std::make_unique<DeckPushButton>("Hobbies"));
	decks.push_back(std::make_unique<DeckPushButton>("Introduction"));
	decks.push_back(std::make_unique<DeckPushButton>("Books"));
	decks.push_back(std::make_unique<DeckPushButton>("Series"));
	for (auto& deck : decks)
	{
		QObject::connect(deck.get(), SIGNAL(clicked()), deck.get(), SLOT(DeckClickSlot()));
		QObject::connect(deck.get(), SIGNAL(DeckClickSignal(const QString&)), &app, SLOT(ReadDeck(const QString&)));
		layout->addWidget(deck.get());
	}

	widget->setLayout(layout);
	scrollArea->setWidget(widget);
}

QScrollArea* Decks::GetWidget()
{
	return scrollArea;
}

void DeckPushButton::DeckClickSlot()
{
	emit DeckClickSignal(text());
}

DeckPushButton::DeckPushButton(const QString& text) : QPushButton(text)
{
	
}
