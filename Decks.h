#pragma once
#include "qobject.h"
#include "QtWidgets/qpushbutton.h"
#include "QtWidgets/qboxlayout.h"
#include "QtWidgets/qwidget.h"

#include <vector>

class Decks : public QObject
{
	Q_OBJECT
public slots:

signals:

public:
	Decks();
private:
	QWidget* widget;
	QVBoxLayout* layout;
	std::vector<std::unique_ptr<QPushButton>> decks;
};

