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

using namespace std;

rotacomputer::rotacomputer() {
	vector<map<string, string>> computedRota(0);
}

rotacomputer::rotacomputer(QListWidget* personListWidget, QListWidget* taskListWidget, int iterations) {
	int numTasks = taskListWidget->count();

	vector<map<string, string>> computedRota(numTasks);

	vector<string> tasks(numTasks);
	vector<string> people(taskListWidget->count());

	for (int taskIndex = 0; taskIndex < numTasks; taskIndex++)
	{
		QListWidgetItem* item = taskListWidget->item(taskIndex);
		tasks[taskIndex] = item->data;
	}

	for (int personIndex = 0; personIndex < people.size; personIndex++) {
		QListWidgetItem* item = personListWidget->item(personIndex);
		people[personIndex] = item->data;
	}

	computeRota(people, tasks, iterations);
}

void rotacomputer::writeToCsv() {
	// Open file stream
	// Write top row as tasks
	// Write remaining rows as people
	// Close file
}

void rotacomputer::computeRota(vector<string> people, vector<string> tasks, int iterations) {
	/* Current approach: Generate a probability of using a particular person
	by summing laziness across all people.
	*/
	vector<pair<string, int>> peopleWithLaziness(people.size());
	double totalInverseLaziness = 0;

	// Split entries into person, laziness
	for (int personIndex = 0; personIndex < people.size(); personIndex++) {
		istringstream stringStream(people[personIndex]);

		string personName;
		stringStream >> personName;

		int laziness;
		stringStream >> laziness;

		peopleWithLaziness[personIndex].first = personName;
		peopleWithLaziness[personIndex].second = laziness;

		totalInverseLaziness += 1/(double)laziness;
	}

	// Calculate normalised laziness
	vector<pair<string, double>> peopleWithNormProb(people.size());
	for (int personIndex = 0; personIndex < people.size(); personIndex++) {
		peopleWithNormProb[personIndex].first = peopleWithLaziness[personIndex].first;
		peopleWithNormProb[personIndex].second = (1/(double)peopleWithLaziness[personIndex].second) / (double)totalInverseLaziness;
	}
	
	// Iterate over iterations
	for (int iter = 0; iter < iterations; iter++) {
		// Iterate through tasks
		for (string task : tasks) {
			// Choose random person for task based on probabilities -> FUNCTION 1
			string randomPerson;
			computedRota[iter][task] = randomPerson;
		}
	}
}

