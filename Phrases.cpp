#include "Phrases.h"

Phrases::Phrases(const QString& deck) : deckName(deck)
{
	Init();
	phrases.push_back(std::make_unique<Phrase>());

	for (auto& phrase : phrases)
	{
		phrasesLayout->addWidget(phrase->GetWidget());
	}
}

Phrases::Phrases(const QString& deckName, std::vector<std::string>& deckPhrasesStr) : deckName(deckName)
{
	Init();
	for (auto& phraseStr : deckPhrasesStr)
	{
		phrases.push_back(std::make_unique<Phrase>(phraseStr));
	}

	for (auto& phrase : phrases)
	{
		phrasesLayout->addWidget(phrase->GetWidget());
	}
}

void Phrases::Init()
{
	layout = new QVBoxLayout;
	widget = new QWidget;
	deckLabel = new QLabel(deckName);
	addPhraseBtn = new QPushButton("Add phrase");
	scrollArea = new QScrollArea;
	phrasesLayout = new QVBoxLayout;
	phrasesWidget = new QWidget;

	deckLabel->setAlignment(Qt::AlignCenter);
	addPhraseBtn->setMaximumWidth(200);
	addPhraseBtn->setMinimumWidth(100);

	QObject::connect(addPhraseBtn, SIGNAL(clicked()), SLOT(AddPhraseSlot()));

	phrasesWidget->setLayout(phrasesLayout);
	scrollArea->setWidgetResizable(true);
	scrollArea->setWidget(phrasesWidget);
	layout->addWidget(deckLabel);
	layout->addWidget(addPhraseBtn);
	layout->addWidget(scrollArea);

	widget->setLayout(layout);
}

QWidget* Phrases::GetWidget()
{
	return widget;
}

std::string Phrases::GetPhraseOutputString()
{
	std::string outputStr = "";
	for (auto& phrase : phrases)
	{
		outputStr += phrase->GetPhraseOutputString() + "\n";
	}
	
	return outputStr;
}

void Phrases::AddPhraseSlot()
{
	auto newPhrase = std::make_unique<Phrase>();
	phrasesLayout->addWidget(newPhrase->GetWidget());
	phrases.push_back(std::move(newPhrase));
}
