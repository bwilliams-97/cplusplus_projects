#include "stdafx.h"
#include "who2clean.h"
#include <iostream>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include <QGridLayout>
#include <QSpinBox>

using namespace std;

Who2Clean::Who2Clean(QWidget *parent)
	: QWidget(parent)
{
    QVBoxLayout* fullWindow = new QVBoxLayout(this);
    QHBoxLayout* chooseOptions = new QHBoxLayout();
    QHBoxLayout* computeBox = new QHBoxLayout();
    QHBoxLayout* showResults = new QHBoxLayout();

    // Choose person
    QVBoxLayout* choosePersonBox = CreateOptionsSection("Person", "Laziness (0-10)");

    // Choose task
    QVBoxLayout* chooseTaskBox = CreateOptionsSection("Task", "Annoyance (0-10)");

    // Add options choices to "options" layout
    chooseOptions->addLayout(choosePersonBox);
    chooseOptions->addLayout(chooseTaskBox);

    // Add top section to window
    fullWindow->addLayout(chooseOptions);

    // Choose iterations
    QGridLayout* computeRow = CreateIterationSection();

    // Add iterations section to window
    fullWindow->addLayout(computeRow);

    //------------Display computation output--------

    setLayout(fullWindow);

	int addPersonCoords[] = { 50,50, 100,100 };
	//this->AddButton("Add", addPersonCoords);
	ui.setupUi(this);

}

QVBoxLayout* Who2Clean::CreateOptionsSection(QString inputName, QString parameterName) {
    QVBoxLayout* chooseOptionBox = new QVBoxLayout();
    QGridLayout* addNewOption = new QGridLayout();

    QLabel* optionText = new QLabel(inputName);
    QLabel* parameterText = new QLabel(parameterName);

    addNewOption->addWidget(optionText, 0, 0);
    addNewOption->addWidget(parameterText, 0, 1);

    QLineEdit* inputOption = new QLineEdit();
    QLineEdit* inputParameter = new QLineEdit();
    QPushButton* addOptionButton = new QPushButton("Add", this);

    addNewOption->addWidget(inputOption, 1, 0);
    addNewOption->addWidget(inputParameter, 1, 1);
    addNewOption->addWidget(addOptionButton, 1, 2);

    QListWidget* optionList = new QListWidget(this);

    chooseOptionBox->addLayout(addNewOption);
    chooseOptionBox->addWidget(optionList);

    // Todo: work out how to use button handlers to alter GUI items.
    //connect(addOptionButton, &QPushButton::clicked, qApp, SLOT (HandleAddButton()));

    return chooseOptionBox;
}

QGridLayout* Who2Clean::CreateIterationSection() {
    QGridLayout* computeRow = new QGridLayout();

    QLabel* iterationsText = new QLabel("Iterations");
    QSpinBox* numIterationsBox = new QSpinBox(this);
    QPushButton* computeButton = new QPushButton("Compute", this);

    computeRow->addWidget(iterationsText, 0, 0);
    computeRow->addWidget(numIterationsBox, 0, 1);
    computeRow->addWidget(computeButton, 0, 2);

    return computeRow;
}

void Who2Clean::HandleAddButton(QLineEdit* optionLine, QLineEdit* parameterLine, QListWidget* optionsList) {
    // Get person and laziness text.
    QString optionString = optionLine->text();
    QString parameterString = parameterLine->text();

    // Append to list
    QString listItem = optionString.append(", ");
    listItem = listItem.append(parameterString);
    optionsList->addItem(listItem);

    // Remove text from line edits
    optionLine->setText("");
    parameterLine->setText("");
}

