#include "Phrase.h"

Phrase::Phrase(QString lang) : language(lang)
{
	layout = new QVBoxLayout;
	langLabel = new QLabel(lang);
	textEdit = new QTextEdit;
	widget = new QWidget;
	deleteBtn = new QPushButton("Delete");
	QObject::connect(deleteBtn, SIGNAL(clicked()), SLOT(DeleteSlot()));

	textEdit->setFixedHeight(60);
	textEdit->setMaximumWidth(200);
	textEdit->setMinimumWidth(100);
	layout->addWidget(langLabel);
	layout->addWidget(textEdit);
	layout->addWidget(deleteBtn);
	widget->setLayout(layout);
}

QWidget* Phrase::GetWidget()
{
	return widget;
}

QString Phrase::GetLanguage()
{
	return language;
}

void Phrase::DeleteSlot()
{
	emit DeleteSignal(language);
}