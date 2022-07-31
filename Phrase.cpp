#include "Phrase.h"

Phrase::Phrase()
{
	layout = new QHBoxLayout();
	addingLangBtn = new QComboBox;
	widget = new QWidget;
	phraseWidget = new QWidget;
	scrollArea = new QScrollArea;
	phraseLayout = new QHBoxLayout;
	editBtn = new QPushButton("Edit");
	editBtn->setCheckable(true);
	editBtn->setStyleSheet("QPushButton{background-color:green;}");

	langs["Russian"] = true;
	langs["Azerbaijani"] = true;
	langs["English"] = true;
	langs["Spanish"] = true;

	addingLangBtn->addItem("Choose language");
	for (auto& lang : langs)
	{
		addingLangBtn->addItem(lang.first);
	}
	QObject::connect(addingLangBtn, SIGNAL(currentTextChanged(const QString&)), SLOT(AddLangSlot(const QString&)));

	widget->setFixedHeight(200);


	phraseWidget->setLayout(phraseLayout);
	scrollArea->setWidgetResizable(true);
	scrollArea->setWidget(phraseWidget);
	layout->addWidget(addingLangBtn);
	layout->addWidget(scrollArea);
	layout->addWidget(editBtn);
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
