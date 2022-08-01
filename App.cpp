#include "App.h"

App::App() : decks(*this), currentDeck("")
{
	layout = new QGridLayout;
	layout->addWidget(decks.GetWidget(), 0, 0, 8, 1);
}

void App::ReadDeck(const QString& deckName)
{
	if (currentDeck == deckName)
	{
		return;
	}

	if (currentDeck != "")
	{
		layout->removeWidget(decksMap[currentDeck]->GetWidget());
		decksMap[currentDeck]->GetWidget()->setParent(nullptr);
	}

	currentDeck = deckName;
	auto iter = decksMap.find(deckName);
	if (iter != decksMap.end())
	{
		layout->addWidget(iter->second->GetWidget(), 0, 1, 7, 3);
		return;
	}
	std::string filename = "decks/" + deckName.toLower().toStdString() + ".txt";
	std::ifstream deckFile;
	deckFile.open(filename);
	if (deckFile.is_open())
	{
		std::vector<std::string> inPhrasesStr;
		std::string tmp;
		while (std::getline(deckFile, tmp))
		{
			inPhrasesStr.push_back(tmp);
		}

		decksMap[deckName] = std::make_unique<Phrases>(deckName, inPhrasesStr);
		layout->addWidget(decksMap[deckName]->GetWidget(), 0, 1, 7, 3);
		deckFile.close();
		return;
	}

	decksMap[deckName] = std::make_unique<Phrases>(deckName);
	layout->addWidget(decksMap[deckName]->GetWidget(), 0, 1, 7, 3);
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
		if (outDeckFile.is_open())
		{
			outDeckFile << deck.second->GetPhraseOutputString();
			outDeckFile.close();
		}
	}
}
