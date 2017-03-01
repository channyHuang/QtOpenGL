#include "graphicsdemo.h"

#include <QHBoxLayout>
#include <QVBoxLayout>

#include <iostream>
using namespace std;

graphicsDemo::graphicsDemo(QWidget *parent)
	:ui(new Ui::graphicsDemo), QWidget(parent)
{
	ui->setupUi(this);
	setGeometry(900, 100, 500, 500);

	initwidgets();

	QVBoxLayout *mainlayout = new QVBoxLayout();
//	mainlayout->addWidget(lightclass);
//	mainlayout->addWidget(bezierclass);
//	mainlayout->addWidget(bspineclass);
	

	setLayout(mainlayout);
}

graphicsDemo::~graphicsDemo()
{
	delete ui;
}

void graphicsDemo::initwidgets()
{
	lightclass = new LightClass();
	bezierclass = new BezierClass();
	bspineclass = new BspineClass();
}

void graphicsDemo::keyPressEvent(QKeyEvent *e)
{
	switch (e->key())
	{
	default:
		break;
	}
}

void graphicsDemo::mousePressEvent(QMouseEvent *e)
{
/*
	//Bezier
	if (e->button() == Qt::LeftButton) {
		//cout << e->x() << " " << e->y() << endl;
		if (bezierclass->flag < 4) {
			bezierPoints[bezierclass->flag].x = (e->x() - 250) / 250.0;
			bezierPoints[bezierclass->flag].y = -(e->y() - 250) / 250.0;
			bezierclass->flag = (bezierclass->flag + 1) % 4;
		}
		bezierclass->update();
	}*/

/*
	//BSpine
	if (e->button() == Qt::LeftButton) {
		if (bspineclass->flag < 4) {
			bspinePoints[bspineclass->flag].x = (e->x() - 250) / 250.0;
			bspinePoints[bspineclass->flag].y = -(e->y() - 250) / 250.0;
			bspineclass->flag = (bspineclass->flag + 1) % 4;
		}
		bspineclass->update();
	}
	*/

	if (e->button() == Qt::LeftButton) {

	}
}