#include "Decks.h"
#include "App.h"

Decks::Decks(App& app)
{
	pApp = &app;
	scrollLayout = new QVBoxLayout;
	layout = new QVBoxLayout;
	widget = new QWidget;
	scrollWidget = new QWidget;
	scrollArea = new QScrollArea;
	addDeckBtn = new QPushButton("Add deck");
	newDeckEdit = new QLineEdit;
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
		scrollLayout->addWidget(deck.get());
	}

	QObject::connect(addDeckBtn, SIGNAL(clicked()), SLOT(AddDeckSlot()));
	scrollArea->setWidgetResizable(true);

	widget->setMaximumWidth(170);
	newDeckEdit->setMaximumWidth(170);
	scrollWidget->setLayout(scrollLayout);
	scrollArea->setWidget(scrollWidget);
	layout->addWidget(newDeckEdit);
	layout->addWidget(addDeckBtn);
	layout->addWidget(scrollArea);
	widget->setLayout(layout);
}

QWidget* Decks::GetWidget()
{
	return widget;
}

void Decks::AddDeckSlot()
{
	if (newDeckEdit->text() == "")
	{
		return;
	}

	auto newDeck = std::make_unique<DeckPushButton>(newDeckEdit->text());
	scrollLayout->addWidget(newDeck.get());
	QObject::connect(newDeck.get(), SIGNAL(clicked()), newDeck.get(), SLOT(DeckClickSlot()));
	QObject::connect(newDeck.get(), SIGNAL(DeckClickSignal(const QString&)), pApp, SLOT(ReadDeck(const QString&)));
	decks.push_back(std::move(newDeck));
}

void DeckPushButton::DeckClickSlot()
{
	emit DeckClickSignal(text());
}

DeckPushButton::DeckPushButton(const QString& text) : QPushButton(text)
{
	
}
