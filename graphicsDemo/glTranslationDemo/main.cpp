#include "gltranslationdemo.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	glTranslationDemo w;
	w.show();
	return a.exec();
}
