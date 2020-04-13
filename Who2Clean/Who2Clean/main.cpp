#include "stdafx.h"
#include "who2clean.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Who2Clean w;

	w.setWindowTitle("Rota Generator");

	w.show();
	return a.exec();
}
