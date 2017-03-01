#include "relightingdraft.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	relightingDraft w;
	w.show();
	return a.exec();
}
