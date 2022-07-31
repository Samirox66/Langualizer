#include "Language.h"

Language::Language(QString lang) : language(lang)
{
	layout = new QVBoxLayout;
	langLabel = new QLabel(lang);
	textEdit = new QTextEdit;
	widget = new QWidget;
	deleteBtn = new QPushButton("Delete");	
	QObject::connect(deleteBtn, SIGNAL(clicked()), SLOT(DeleteSlot()));

	widget->setFixedHeight(150);
	textEdit->setFixedHeight(60);
	textEdit->setMaximumWidth(200);
	textEdit->setMinimumWidth(100);
	deleteBtn->setMaximumWidth(200);
	deleteBtn->setMinimumWidth(200);
	layout->addWidget(langLabel);
	layout->addWidget(textEdit);
	layout->addWidget(deleteBtn);
	widget->setLayout(layout);
}

QWidget* Language::GetWidget()
{
	return widget;
}

QString Language::GetLanguage()
{
	return language;
}

std::string Language::GetPhraseOutputString()
{
	return language.toStdString() + " " + textEdit->toPlainText().toStdString() + " ";
}

void Language::DeleteSlot()
{
	emit DeleteSignal(language);
}

void Language::ChangeEditability(bool isEditable)
{
	textEdit->setEnabled(isEditable);
}
