#include "glprojectiondemo.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>

#include "data.h"
#include <iostream>

glProjectionDemo::glProjectionDemo(QWidget *parent)
	:ui(new Ui::glProjectionDemo), QWidget(parent)
{
	ui->setupUi(this);

	initwidgets();
	initconnects();
	//params
	QGridLayout *projparamlayout = new QGridLayout();
	projparamlayout->addWidget(new QLabel("Left"), 0, 0, 1, 1);
	projparamlayout->addWidget(new QLabel("Right"), 1, 0, 1, 1);
	projparamlayout->addWidget(new QLabel("Bottom"), 2, 0, 1, 1);
	projparamlayout->addWidget(new QLabel("Top"), 3, 0, 1, 1);
	projparamlayout->addWidget(new QLabel("Near"), 4, 0, 1, 1);
	projparamlayout->addWidget(new QLabel("Far"), 5, 0, 1, 1);
	projparamlayout->addWidget(leftbox, 0, 1, 1, 1);
	projparamlayout->addWidget(rightbox, 1, 1, 1, 1);
	projparamlayout->addWidget(bottombox, 2, 1, 1, 1);
	projparamlayout->addWidget(topbox, 3, 1, 1, 1);
	projparamlayout->addWidget(nearbox, 4, 1, 1, 1);
	projparamlayout->addWidget(farbox, 5, 1, 1, 1);

	QGroupBox *projparambox = new QGroupBox("Projection Params");
	projparambox->setLayout(projparamlayout);
	//button
	QVBoxLayout *btnlayout = new QVBoxLayout();
	btnlayout->addWidget(persbtn);
	btnlayout->addWidget(orthobtn);
	QGroupBox *btnbox = new QGroupBox("Projection Type");
	btnbox->setLayout(btnlayout);
	//matrix
	showmatrix();
	projmatrixbox->setLayout(matrixlayout);
	//gl widgets
	QVBoxLayout *showlayout = new QVBoxLayout();
	showlayout->addWidget(glwindow);
	showlayout->addWidget(glwindow3d);
	//all params
	QGridLayout *paramlayout = new QGridLayout();
	paramlayout->addWidget(btnbox, 0, 0, 1, 1);
	paramlayout->addWidget(resetbtn, 0, 1, 1, 1);
	paramlayout->addWidget(projparambox, 1, 0, 1, 1);
	paramlayout->addWidget(projmatrixbox, 1, 1, 1, 1);
	//main
	QHBoxLayout *mainlayout = new QHBoxLayout();
	mainlayout->addLayout(showlayout);
	mainlayout->addLayout(paramlayout);

	setLayout(mainlayout);
}

glProjectionDemo::~glProjectionDemo()
{
	delete ui;
}

void glProjectionDemo::initwidgets()
{
	glwindow = new glWindow();
	glwindow3d = new glWindow3D();

	resetbtn = new QPushButton("Reset");

	projmatrixbox = new QGroupBox("Projection Matrix");
	matrixlayout = new QGridLayout();

	leftbox = new QDoubleSpinBox();
	leftbox->setRange(-10, 10);
	leftbox->setSingleStep(0.1);
	rightbox = new QDoubleSpinBox();
	rightbox->setRange(-10, 10);
	rightbox->setSingleStep(0.1);
	bottombox = new QDoubleSpinBox();
	bottombox->setRange(-10, 10);
	bottombox->setSingleStep(0.1);
	topbox = new QDoubleSpinBox();
	topbox->setRange(-10, 10);
	topbox->setSingleStep(0.1);
	nearbox = new QSpinBox();
	nearbox->setRange(1, 100);
	farbox = new QSpinBox();
	farbox->setRange(1, 100);

	persbtn = new QRadioButton("Perspective");
	persbtn->setChecked(true);
	orthobtn = new QRadioButton("Orthographic");

	reset();
}

void glProjectionDemo::initconnects()
{
	connect(resetbtn, SIGNAL(clicked()), this, SLOT(reset()));

	connect(leftbox, SIGNAL(valueChanged(double)), this, SLOT(computeMatrix()));
	connect(rightbox, SIGNAL(valueChanged(double)), this, SLOT(computeMatrix()));
	connect(bottombox, SIGNAL(valueChanged(double)), this, SLOT(computeMatrix()));
	connect(topbox, SIGNAL(valueChanged(double)), this, SLOT(computeMatrix()));
	connect(nearbox, SIGNAL(valueChanged(int)), this, SLOT(computeMatrix()));
	connect(farbox, SIGNAL(valueChanged(int)), this, SLOT(computeMatrix()));

	connect(persbtn, SIGNAL(clicked()), this, SLOT(computeMatrix()));
	connect(orthobtn, SIGNAL(clicked()), this, SLOT(computeMatrix()));
}

void glProjectionDemo::reset()
{
	leftbox->setValue(-0.5);
	rightbox->setValue(0.5);
	bottombox->setValue(-0.5);
	topbox->setValue(0.5);
	nearbox->setValue(1);
	farbox->setValue(10);

	computeMatrix();
}

void glProjectionDemo::computeMatrix()
{
	left = leftbox->value();
	right = rightbox->value();
	top = topbox->value();
	bottom = bottombox->value();
	nearnum = nearbox->value();
	farnum = farbox->value();
	//perspective
	if (persbtn->isChecked()) {
		projtype = true;
		projmatrix = Diag(4);
		projmatrix(0, 0) = 2 * nearnum / (right - left);
		projmatrix(0, 2) = (right + left) / (right - left);
		projmatrix(1, 1) = 2 * nearnum / (top - bottom);
		projmatrix(1, 2) = (top + bottom) / (top - bottom);
		projmatrix(2, 2) = -(farnum + nearnum) / (farnum - nearnum);
		projmatrix(2, 3) = -(2 * farnum *nearnum) / (farnum - nearnum);
		projmatrix(3, 2) = -1;
		projmatrix(3, 3) = 0;
	}
	//orthographic
	else {
		projtype = false;
		projmatrix = Diag(4);
		projmatrix(0, 0) = 2 / (right - left);
		projmatrix(0, 3) = -(right + left) / (right - left);
		projmatrix(1, 1) = 2 / (top - bottom);
		projmatrix(1, 3) = -(top + bottom) / (top - bottom);
		projmatrix(2, 2) = -2 / (farnum - nearnum);
		projmatrix(2, 3) = -(farnum + nearnum) / (farnum - nearnum);
	}

	showmatrix();
}

void glProjectionDemo::showmatrix()
{
	while (matrixlayout->count() > 0) {
		QWidget *widget = matrixlayout->itemAt(0)->widget();
		matrixlayout->removeWidget(widget);
		delete widget;
	}
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			matrixlayout->addWidget(new QLabel(QString::number(projmatrix.get(i, j))), i, j, 1, 1);
		}
	}
}
