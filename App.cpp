#include "App.h"

App::App() : decks(*this)
{
	layout = new QGridLayout;
	layout->addWidget(decks.GetWidget(), 0, 0, 8, 1);
}

void App::ReadDeck(const QString& deckName)
{
	auto iter = decksMap.find(deckName);
	if (iter != decksMap.end())
	{
		layout->addWidget(iter->second->GetWidget(), 0, 1, 7, 3);
		return;
	}
	std::string filename = "decks/" + deckName.toLower().toStdString() + ".txt";
	std::ifstream deckFile(filename);
	if (!deckFile)
	{
		decksMap[deckName] = std::make_unique<Phrases>(deckName);
		layout->addWidget(decksMap[deckName]->GetWidget(), 0, 1, 7, 3);
	}
}

QGridLayout* App::GetLayout()
{
	return layout;
}

App::~App()
{
	WritePhrases();
}

void App::WritePhrases()
{
	for (auto& deck : decksMap)
	{
		std::string filename = "decks/" + deck.first.toLower().toStdString() + ".txt";
		std::ofstream outDeckFile(filename);
		outDeckFile << deck.second->GetPhraseOutputString();
	}
}
