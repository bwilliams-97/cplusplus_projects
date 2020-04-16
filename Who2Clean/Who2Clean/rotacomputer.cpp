#include "stdafx.h"
#include "rotacomputer.h"
#include <QListWidget>
#include <vector>
#include <map>
#include <fstream>
#include <iostream>
#include <string.h>
#include <sstream>
#include <string>
#include <stdlib.h>
#include <time.h>

using namespace std;

rotacomputer::rotacomputer(QListWidget* personListWidget, QListWidget* taskListWidget, int iterations) {
	// Link function to compute button
	// Display table somehow inside window?
	int numTasks = taskListWidget->count();

	vector<map<int, string>> computedRotaInit(iterations);
	computedRota = computedRotaInit;

	vector<string> tasks(numTasks);
	vector<string> people(taskListWidget->count());

	for (int taskIndex = 0; taskIndex < numTasks; taskIndex++)
	{
		QListWidgetItem* item = taskListWidget->item(taskIndex);
		tasks[taskIndex] = item->text().toStdString();
	}

	for (int personIndex = 0; personIndex < people.size(); personIndex++) {
		QListWidgetItem* item = personListWidget->item(personIndex);
		people[personIndex] = item->text().toStdString();
	}

	computeRota(people, tasks, iterations);

	writeToCsv(tasks);
}

void rotacomputer::writeToCsv(vector<string> tasks) {
	// Open file stream
	std::ofstream csvfile;
	csvfile.open("rota.csv");

	// Write top row as tasks
	ostringstream topRow;
	topRow << "Task";
	for (string taskName : tasks) {
		topRow << "," + taskName;
	}
	csvfile << topRow.str() + "\n";

	// Write remaining rows as people
	int iter_idx = 0;
	for (map<int, string> iteration : computedRota) {
		ostringstream currentRow;
		currentRow << "Iteration: " + to_string(iter_idx++);
		for (int taskIndex = 0; taskIndex < iteration.size(); taskIndex++) {
			currentRow << "," + iteration[taskIndex];
		}
		csvfile << currentRow.str() + "\n";
	}

	// Close file
	csvfile.close();
}

void rotacomputer::computeRota(vector<string> people, vector<string> tasks, int iterations) {
	/* Current approach: Generate a probability of using a particular person
	by summing laziness across all people.
	*/

	// Initialise random seed
	srand(time(NULL));

	vector<int> personLaziness(people.size());
	vector<string> peopleNames(people.size());

	double totalInverseLaziness = 0;

	// Split entries into person, laziness
	for (int personIndex = 0; personIndex < people.size(); personIndex++) {
		istringstream stringStream(people[personIndex]);

		string personName;
		stringStream >> personName;
		peopleNames[personIndex] = personName;

		int laziness;
		stringStream >> laziness;

		personLaziness[personIndex] = laziness;

		totalInverseLaziness += 1/(double)laziness;
	}

	// Calculate normalised laziness
	vector<double> personProbs(people.size());
	for (int personIndex = 0; personIndex < people.size(); personIndex++) {
		personProbs[personIndex] = (1/(double)personLaziness[personIndex]) / (double)totalInverseLaziness;
	}
	
	// Iterate over iterations
	for (int iter = 0; iter < iterations; iter++) {
		// Iterate through tasks
		for (int taskIndex = 0; taskIndex < tasks.size(); taskIndex++) {
			// Choose random person for task based on probabilities
			computedRota[iter][taskIndex] = chooseRand(peopleNames, personProbs);
		}
	}
}

string chooseRand(vector<string> choices, vector<double> probabilities) {
	double randNum = rand() / double(RAND_MAX);
	
	double currentSum = 0.0;
	int personIndex = 0;

	string choice;

	while (currentSum < 1.0) {
		currentSum += probabilities[personIndex];
		if (randNum < currentSum) {
			choice = choices[personIndex];
			break;
		}
		personIndex++;
	}

	return choice;
}

