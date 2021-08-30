#include "nehewidget.h"
#include <QtWidgets/QApplication>
#include <QMessageBox>

int main(int argc, char *argv[])
{
	bool fs=false;
	QApplication a(argc, argv);
	switch(QMessageBox::information(0,"FullScreen?","Fullscreen or not?",QMessageBox::Yes,QMessageBox::No|QMessageBox::Default)) {
	case QMessageBox::Yes:
		fs=true;
		break;
	case QMessageBox::No:
		fs=false;
		break;
	}
	nehewidget w(0,fs);
	w.show();
	return a.exec();
}
