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
    std::pair<QVBoxLayout*, RotaOptions> personOptionsSection = CreateOptionsSection("Person", "Laziness (0-10)");
    QBoxLayout* choosePersonBox = personOptionsSection.first;
    this->personOptions = personOptionsSection.second;

    // Choose task
    std::pair<QVBoxLayout*, RotaOptions> taskOptionsSection = CreateOptionsSection("Task", "Annoyance (0-10)");
    QBoxLayout* chooseTaskBox = taskOptionsSection.first;
    this->taskOptions = taskOptionsSection.second;

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

RotaOptions::RotaOptions() {
    this->optionsList = new QListWidget();
    this->optionName = new QLineEdit();
    this->optionParameter = new QLineEdit();
}

RotaOptions::RotaOptions(QListWidget* listWidget, QLineEdit* optName, QLineEdit* optParam) {
    this->optionsList = listWidget;
    this->optionName = optName;
    this->optionParameter = optParam;
}

std::pair<QVBoxLayout*, RotaOptions> Who2Clean::CreateOptionsSection(QString inputName, QString parameterName) {
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
    QPushButton* clearButton = new QPushButton("Clear", this);

    chooseOptionBox->addLayout(addNewOption);
    chooseOptionBox->addWidget(optionList);
    chooseOptionBox->addWidget(clearButton);
    
    if (inputName == "Person") {
        connect(addOptionButton, SIGNAL (clicked()), this, SLOT (HandleAddPersonButton()));
        connect(clearButton, SIGNAL(clicked()), this, SLOT(HandleClearPersonButton()));
    }
    else if (inputName == "Task") {
        connect(addOptionButton, SIGNAL(clicked()), this, SLOT (HandleAddTaskButton()));
        connect(clearButton, SIGNAL(clicked()), this, SLOT(HandleClearTaskButton()));
    }

    RotaOptions rotaOptions = RotaOptions(optionList, inputOption, inputParameter);

    return make_pair(chooseOptionBox, rotaOptions);
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

void Who2Clean::HandleClearPersonButton() {
    HandleClearButton(personOptions);
}

void Who2Clean::HandleClearTaskButton() {
    HandleClearButton(taskOptions);
}

void Who2Clean::HandleClearButton(RotaOptions options) {
    options.optionsList->clear();
}

void Who2Clean::HandleAddPersonButton() {
    HandleAddButton(personOptions);
}

void Who2Clean::HandleAddTaskButton() {
    HandleAddButton(taskOptions);
}

void Who2Clean::HandleAddButton(RotaOptions options) {
    // Get person and laziness text.
    QString optionString = options.optionName->text();
    QString parameterString = options.optionParameter->text();

    // Append to list
    QString listItem = optionString.append(", ");
    listItem = listItem.append(parameterString);
    options.optionsList->addItem(listItem);

    // Remove text from line edits
    options.optionName->setText("");
    options.optionParameter->setText("");
}

