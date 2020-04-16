#pragma once

#include <QtWidgets/QWidget>
#include <QListWidget>
#include <QLineEdit>
#include <map>
#include <vector>

using namespace std;

class rotacomputer
{
public:
	rotacomputer(QListWidget*, QListWidget*, int);

	void writeToCsv(vector<string>);

	vector<map<int, string>> computedRota;

private:
	void computeRota(vector<string>, vector<string>, int);
};

string chooseRand(vector<string>, vector<double>);
