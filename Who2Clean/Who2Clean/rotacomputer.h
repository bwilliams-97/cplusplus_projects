#pragma once

#include <QtWidgets/QWidget>
#include <QListWidget>
#include <QLineEdit>
#include <map>
#include <vector>

class rotacomputer
{
public:
	rotacomputer();
	rotacomputer(QListWidget*, QListWidget*, int);

	void writeToCsv();

	std::vector<std::map<std::string, std::string>> computedRota;

private:
	void computeRota(vector<string>, vector<string>, int);
};

