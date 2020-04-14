#pragma once

#include <QtWidgets/QWidget>
#include <QListWidget>
#include <QLineEdit>
#include "ui_who2clean.h"

class RotaOptions
{
public:
	RotaOptions();
	RotaOptions(QListWidget*, QLineEdit*, QLineEdit*);
	QListWidget* optionsList;
	QLineEdit* optionName;
	QLineEdit* optionParameter;
};

class Who2Clean : public QWidget
{
	Q_OBJECT

public:
	Who2Clean(QWidget *parent = Q_NULLPTR);

private slots:
	void HandleAddPersonButton();
	void HandleAddTaskButton();
	void HandleClearPersonButton();
	void HandleClearTaskButton();

private:
	Ui::Who2CleanClass ui;
	std::pair<QVBoxLayout*, RotaOptions> CreateOptionsSection(QString, QString);
	QGridLayout* CreateIterationSection();
	void HandleAddButton(RotaOptions);
	void HandleClearButton(RotaOptions);

	RotaOptions personOptions;
	RotaOptions taskOptions;
};
