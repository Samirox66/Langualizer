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
	ReadDecks();
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

void Decks::ReadDecks()
{
	std::string filename = "decks/decks.txt";
	std::ifstream decksFile;
	decksFile.open(filename);
	if (decksFile.is_open())
	{
		std::string deck;
		while (std::getline(decksFile, deck))
		{
			decks.push_back(std::make_unique<DeckPushButton>(QString::fromStdString(deck)));
		}

		decksFile.close();
	}
}

void Decks::AddDeckSlot()
{
	QString newDeckStr = newDeckEdit->text();
	if (newDeckStr == "")
	{
		return;
	}

	for (auto& deck : decks)
	{
		if (deck->text() == newDeckStr)
		{
			return;
		}
	}

	std::string filename = "decks/decks.txt";
	std::ofstream decksFile;
	decksFile.open(filename, std::ios::app);
	if (decksFile.is_open())
	{
		decksFile << newDeckStr.toStdString() << std::endl;
		decksFile.close();
	}

	auto newDeck = std::make_unique<DeckPushButton>(newDeckStr);
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
