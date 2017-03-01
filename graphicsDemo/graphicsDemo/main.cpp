#include "graphicsdemo.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	graphicsDemo w;
	w.show();
	return a.exec();
}
