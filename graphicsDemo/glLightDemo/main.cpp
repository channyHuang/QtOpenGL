#include "gllightdemo.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	glLightDemo w;
	w.show();
	return a.exec();
}
