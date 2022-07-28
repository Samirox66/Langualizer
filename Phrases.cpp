#include "Phrases.h"

Phrases::Phrases()
{
	layout = new QHBoxLayout();
	addingLangButton = new QComboBox;
	widget = new QWidget;

	langs["Russian"] = std::make_pair(1, true);
	langs["Azerbaijani"] = std::make_pair(2, true);
	langs["English"] = std::make_pair(3, true);
	langs["Spanish"] = std::make_pair(4, true);

	addingLangButton->addItem("Choose language");
	for (auto& lang : langs)
	{
		addingLangButton->addItem(lang.first);
	}
	QObject::connect(addingLangButton, SIGNAL(currentTextChanged(const QString&)), SLOT(AddLangSlot(const QString&)));

	layout->addWidget(addingLangButton);
	widget->setLayout(layout);
}

void Phrases::AddLangSlot(const QString& lang)
{
	if (lang != "Choose language")
	{
		langs[lang] = std::make_pair(-1, false);
		auto phrase = std::make_unique<Phrase>(lang);
		QObject::connect(phrase.get(), SIGNAL(DeleteSignal(const QString&)), SLOT(DeleteLangSlot(const QString&)));
		layout->addWidget(phrase->GetWidget());
		phrases.push_back(std::move(phrase));
		int index = addingLangButton->findText(lang);
		addingLangButton->blockSignals(true);
		addingLangButton->removeItem(index);
		addingLangButton->setCurrentIndex(0);
		addingLangButton->blockSignals(false);
		for (auto& language : langs)
		{
			if (language.second.second && language.second.first > langs[lang].first)
			{
				language.second.first--;
			}
		}
	}
}

void Phrases::DeleteLangSlot(const QString& lang)
{
	int availableLangs = std::count_if(langs.begin(), langs.end(), [](std::pair<const QString, std::pair<int, bool>>& x) { return x.second.second; });
	langs[lang] = std::make_pair(availableLangs + 1, true);
	addingLangButton->addItem(lang);
	/*std::list<std::unique_ptr<Phrase>>::const_iterator iter = std::move(std::find_if(phrases.begin(), phrases.end(), [&lang](std::unique_ptr<Phrase> phrase) { return phrase->GetLanguage() == lang; }));
	phrases.erase(iter);
	layout->removeWidget(iter->get()->GetWidget());*/
	for (auto& phrase : phrases)
	{
		if (phrase->GetLanguage() == lang)
		{
			layout->removeWidget(phrase->GetWidget());
			delete phrase->GetWidget();
		}
	}
}

QWidget* Phrases::GetWidget()
{
	return widget;
}
