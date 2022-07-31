#include "Phrases.h"

Phrases::Phrases(const QString& deck) : deckName(deck)
{
	layout = new QVBoxLayout;
	widget = new QWidget;
	deckLabel = new QLabel(deck);
	addPhraseBtn = new QPushButton("Add phrase");
	scrollArea = new QScrollArea;
	phrasesLayout = new QVBoxLayout;
	phrasesWidget = new QWidget;
	phrases.push_back(std::make_unique<Phrase>());

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
	for (auto& phrase : phrases)
	{
		phrasesLayout->addWidget(phrase->GetWidget());
	}

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
