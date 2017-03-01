#include "glprojectiondemo.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	glProjectionDemo w;
	w.show();
	return a.exec();
}
