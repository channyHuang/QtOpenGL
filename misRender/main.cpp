#include "misrender.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	misRender w;
	w.show();
	return a.exec();
}
