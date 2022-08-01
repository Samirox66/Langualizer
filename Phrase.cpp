#include "Phrase.h"

Phrase::Phrase()
{
	Init();
	for (auto& lang : langs)
	{
		addingLangBtn->addItem(lang.first);
	}
}

Phrase::Phrase(const std::string& phraseStr)
{
	Init();
	std::map<QString, QString> phraseMap;
	std::vector<std::string> words;
	std::istringstream iss(phraseStr);
	std::copy(std::istream_iterator<std::string>(iss),
		std::istream_iterator<std::string>(),
		std::back_inserter<std::vector<std::string>>(words));
	QString lang = "";
	QString phraseInLang = "";
	for (auto& word : words)
	{
		if (word.at(0) == '~' && lang != "")
		{
			phraseMap[lang] = phraseInLang;
			lang = "";
			phraseInLang = "";
		}
		if (lang == "")
		{
			lang = QString::fromStdString(word.substr(1, word.size() - 1));
		}
		else
		{
			if (phraseInLang != "")
			{
				phraseInLang += " ";
			}
			phraseInLang += QString::fromStdString(word);
		}
	}

	if (lang != "" && phraseInLang != "")
	{
		phraseMap[lang] = phraseInLang;
	}

	for (auto& phrasePair : phraseMap)
	{
		langs[phrasePair.first] = false;
		auto phrase = std::make_unique<Language>(phrasePair.first, phrasePair.second);
		QObject::connect(phrase.get(), SIGNAL(DeleteSignal(const QString&)), SLOT(DeleteLangSlot(const QString&)));
		QObject::connect(editBtn, SIGNAL(toggled(bool)), phrase.get(), SLOT(ChangeEditability(bool)));
		phraseLayout->addWidget(phrase->GetWidget());
		pLanguages.push_back(std::move(phrase));
	}
	
	for (auto& lang : langs)
	{
		if (lang.second)
		{
			addingLangBtn->addItem(lang.first);
		}
	}
}

void Phrase::Init()
{
	layout = new QHBoxLayout();
	addingLangBtn = new QComboBox;
	widget = new QWidget;
	phraseWidget = new QWidget;
	buttonsWidget = new QWidget;
	scrollArea = new QScrollArea;
	phraseLayout = new QHBoxLayout;
	buttonsLayout = new QVBoxLayout;
	editBtn = new QPushButton("Edit");
	deleteBtn = new QPushButton("Delete");
	editBtn->setCheckable(true);
	editBtn->setStyleSheet("QPushButton{background-color:green;}");

	langs["Russian"] = true;
	langs["Azerbaijani"] = true;
	langs["English"] = true;
	langs["Spanish"] = true;

	addingLangBtn->addItem("Choose language");
	QObject::connect(addingLangBtn, SIGNAL(currentTextChanged(const QString&)), SLOT(AddLangSlot(const QString&)));
	scrollArea->setWidgetResizable(true);

	buttonsLayout->addWidget(addingLangBtn);
	buttonsLayout->addWidget(editBtn);
	buttonsLayout->addWidget(deleteBtn);
	widget->setFixedHeight(200);
	phraseWidget->setLayout(phraseLayout);
	buttonsWidget->setLayout(buttonsLayout);
	scrollArea->setWidget(phraseWidget);
	layout->addWidget(buttonsWidget);
	layout->addWidget(scrollArea);
	widget->setLayout(layout);
}

void Phrase::AddLangSlot(const QString& lang)
{
	if (lang != "Choose language" && editBtn->isChecked())
	{
		langs[lang] = false;
		auto phrase = std::make_unique<Language>(lang);
		QObject::connect(phrase.get(), SIGNAL(DeleteSignal(const QString&)), SLOT(DeleteLangSlot(const QString&)));
		QObject::connect(editBtn, SIGNAL(toggled(bool)), phrase.get(), SLOT(ChangeEditability(bool)));
		phraseLayout->addWidget(phrase->GetWidget());
		pLanguages.push_back(std::move(phrase));
		int index = addingLangBtn->findText(lang);
		addingLangBtn->blockSignals(true);
		addingLangBtn->removeItem(index);
		addingLangBtn->setCurrentIndex(0);
		addingLangBtn->blockSignals(false);
	}
}

void Phrase::DeleteLangSlot(const QString& lang)
{
	if (editBtn->isChecked())
	{
		int availableLangs = std::count_if(langs.begin(), langs.end(), [](std::pair<const QString, bool>& x) { return x.second; });
		langs[lang] = true;
		addingLangBtn->addItem(lang);
		for (auto& phrase : pLanguages)
		{
			if (phrase->GetLanguage() == lang)
			{
				phraseLayout->removeWidget(phrase->GetWidget());
				delete phrase->GetWidget();
			}
		}
	}
}

QWidget* Phrase::GetWidget()
{
	return widget;
}

std::string Phrase::GetPhraseOutputString()
{
	std::string outputStr = "";
	for (auto& language : pLanguages)
	{
		outputStr += language->GetPhraseOutputString();
	}

	return outputStr;
}
