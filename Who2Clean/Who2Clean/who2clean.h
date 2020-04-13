#pragma once

#include <QtWidgets/QWidget>
#include "ui_who2clean.h"

class Who2Clean : public QWidget
{
	Q_OBJECT

public:
	Who2Clean(QWidget *parent = Q_NULLPTR);

private slots:
	void HandleAddButton();

private:
	Ui::Who2CleanClass ui;
	QVBoxLayout* CreateOptionsSection(QString, QString);
	QGridLayout* CreateIterationSection();
};
