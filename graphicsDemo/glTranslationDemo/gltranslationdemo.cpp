#include "gltranslationdemo.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QMessageBox>

#include "data.h"

#include <iostream>
using namespace std;

glTranslationDemo::glTranslationDemo(QWidget *parent)
	:ui(new Ui::glTranslationDemo), QWidget(parent)
{
	ui->setupUi(this);

	initwidgets();
	initconnects();

	resetmatrix();
	
	QVBoxLayout *glwindowlayout = new QVBoxLayout();
	glwindowlayout->addWidget(glwindow);
	glwindowlayout->addWidget(glwindow3d);
	
	QGridLayout *viewparamlayout = new QGridLayout();
	viewparamlayout->addWidget(new QLabel("Position"), 1, 0, 1, 1);
	viewparamlayout->addWidget(new QLabel("X"), 0, 1, 1, 1);
	viewparamlayout->addWidget(viewxbox, 0, 2, 1, 3);
	viewparamlayout->addWidget(resetviewbtn, 0, 5, 1, 1);
	viewparamlayout->addWidget(new QLabel("Y"), 1, 1, 1, 1);
	viewparamlayout->addWidget(viewybox, 1, 2, 1, 3);
	viewparamlayout->addWidget(new QLabel("Z"), 2, 1, 1, 1);
	viewparamlayout->addWidget(viewzbox, 2, 2, 1, 3);
	viewparamlayout->addWidget(new QLabel("Pitch(X)"), 3, 1, 1, 1);
	viewparamlayout->addWidget(pitchbox, 3, 2, 1, 3);
	viewparamlayout->addWidget(new QLabel("Yaw(Y)"), 4, 1, 1, 1);
	viewparamlayout->addWidget(yawbox, 4, 2, 1, 3);
	viewparamlayout->addWidget(new QLabel("Roll(Z)"), 5, 1, 1, 1);
	viewparamlayout->addWidget(rollbox, 5, 2, 1, 3);

	viewparambox->setLayout(viewparamlayout);
	
	QGridLayout *modelparamlayout = new QGridLayout();
	modelparamlayout->addWidget(new QLabel("Position"), 1, 0, 1, 1);
	modelparamlayout->addWidget(new QLabel("X"), 0, 1, 1, 1);
	modelparamlayout->addWidget(modelxbox, 0, 2, 1, 3);
	modelparamlayout->addWidget(resetmodelbtn, 0, 5, 1, 1);
	modelparamlayout->addWidget(new QLabel("Y"), 1, 1, 1, 1);
	modelparamlayout->addWidget(modelybox, 1, 2, 1, 3);
	modelparamlayout->addWidget(new QLabel("Z"), 2, 1, 1, 1);
	modelparamlayout->addWidget(modelzbox, 2, 2, 1, 3);
	modelparamlayout->addWidget(new QLabel("Rotation"), 4, 0, 1, 1);
	modelparamlayout->addWidget(new QLabel("X"), 3, 1, 1, 1);
	modelparamlayout->addWidget(rotxbox, 3, 2, 1, 3);
	modelparamlayout->addWidget(new QLabel("Y"), 4, 1, 1, 1);
	modelparamlayout->addWidget(rotybox, 4, 2, 1, 3);
	modelparamlayout->addWidget(new QLabel("Z"), 5, 1, 1, 1);
	modelparamlayout->addWidget(rotzbox, 5, 2, 1, 3);

	modelparambox->setLayout(modelparamlayout);

	modelviewmatrixshow = new QGridLayout();
	modelviewbox->setLayout(modelviewmatrixshow);
	viewmatrixshow = new QGridLayout();
	viewmatrixbox->setLayout(viewmatrixshow);
	modelmatrixshow = new QGridLayout();
	modelmatrixbox->setLayout(modelmatrixshow);
	showmatrix();

	QHBoxLayout *matrixlayout = new QHBoxLayout();
	matrixlayout->addWidget(modelviewbox);
	matrixlayout->addWidget(new QLabel("="));
	matrixlayout->addWidget(viewmatrixbox);
	matrixlayout->addWidget(new QLabel("X"));
	matrixlayout->addWidget(modelmatrixbox);

	QVBoxLayout *paramlayout = new QVBoxLayout();
	paramlayout->addWidget(viewparambox);
	paramlayout->addWidget(modelparambox);
	paramlayout->addLayout(matrixlayout);
	
	QHBoxLayout *mainlayout = new QHBoxLayout();
	mainlayout->addLayout(glwindowlayout);
	mainlayout->addLayout(paramlayout);

	setLayout(mainlayout);
}

glTranslationDemo::~glTranslationDemo()
{
	delete ui;
}

void glTranslationDemo::initwidgets()
{
	viewparambox = new QGroupBox("View(Camera)");
	modelparambox = new QGroupBox("Model");

	modelviewbox = new QGroupBox("ModelView Matrix");
	viewmatrixbox = new QGroupBox("View Matrix");
	modelmatrixbox = new QGroupBox("Model Matrix");

	viewxbox = new QSpinBox();
	viewxbox->setRange(-10, 10);
	viewybox = new QSpinBox();
	viewybox->setRange(-10, 10);
	viewzbox = new QSpinBox();
	viewzbox->setRange(-10, 10);
//	viewzbox->setValue(10);
	modelxbox = new QSpinBox();
	modelxbox->setRange(-10, 10);
	modelybox = new QSpinBox();
	modelybox->setRange(-10, 10);
	modelzbox = new QSpinBox();
	modelzbox->setRange(-10, 10);

	pitchbox = new QSpinBox();
	pitchbox->setRange(0, 360);
	rollbox = new QSpinBox();
	rollbox->setRange(0, 360);
	yawbox = new QSpinBox();
	yawbox->setRange(0, 360);
	rotxbox = new QSpinBox();
	rotxbox->setRange(0, 360);
	rotybox = new QSpinBox();
	rotybox->setRange(0, 360);
	rotzbox = new QSpinBox();
	rotzbox->setRange(0, 360);

	glwindow = new glWindow();
	glwindow3d = new glWindow3D();

	resetviewbtn = new QPushButton("Reset");
	resetmodelbtn = new QPushButton("Reset");
}

void glTranslationDemo::initconnects()
{
	connect(resetviewbtn, SIGNAL(clicked()), this, SLOT(resetview()));
	connect(resetmodelbtn, SIGNAL(clicked()), this, SLOT(resetmodel()));

	connect(viewxbox, SIGNAL(valueChanged(int)), this, SLOT(computeMatrix()));
	connect(viewybox, SIGNAL(valueChanged(int)), this, SLOT(computeMatrix()));
	connect(viewzbox, SIGNAL(valueChanged(int)), this, SLOT(computeMatrix()));
	connect(modelxbox, SIGNAL(valueChanged(int)), this, SLOT(computeMatrix()));
	connect(modelybox, SIGNAL(valueChanged(int)), this, SLOT(computeMatrix()));
	connect(modelzbox, SIGNAL(valueChanged(int)), this, SLOT(computeMatrix()));
	connect(rotxbox, SIGNAL(valueChanged(int)), this, SLOT(computeMatrix()));
	connect(rotybox, SIGNAL(valueChanged(int)), this, SLOT(computeMatrix()));
	connect(rotzbox, SIGNAL(valueChanged(int)), this, SLOT(computeMatrix()));
	connect(rollbox, SIGNAL(valueChanged(int)), this, SLOT(computeMatrix()));
	connect(pitchbox, SIGNAL(valueChanged(int)), this, SLOT(computeMatrix()));
	connect(yawbox, SIGNAL(valueChanged(int)), this, SLOT(computeMatrix()));
}

void glTranslationDemo::resetview()
{
	viewxbox->setValue(0);
	viewybox->setValue(0);
	viewzbox->setValue(0);

	pitchbox->setValue(0);
	yawbox->setValue(0);
	rollbox->setValue(0);
}

void glTranslationDemo::resetmodel()
{
	modelxbox->setValue(0);
	modelybox->setValue(0);
	modelzbox->setValue(0);

	rotxbox->setValue(0);
	rotybox->setValue(0);
	rotzbox->setValue(0);
}

void glTranslationDemo::computeMatrix()
{
	viewx = viewxbox->value();
	viewy = viewybox->value();
	viewz = viewzbox->value();

	rotx = rotxbox->value();
	roty = rotybox->value();
	rotz = rotzbox->value();

	viewmatrix(0, 3) = viewxbox->text().toInt();
	viewmatrix(1, 3) = viewybox->text().toInt();
	viewmatrix(2, 3) = -viewzbox->text().toInt();

	modelmatrix(0, 3) = modelxbox->text().toInt();
	modelmatrix(1, 3) = modelybox->text().toInt();
	modelmatrix(2, 3) = modelzbox->text().toInt();

	modelview = viewmatrix*modelmatrix;

	showmatrix();
}

void glTranslationDemo::resetmatrix()
{
	modelview = Diag(4);
	viewmatrix = Diag(4);
	modelmatrix = Diag(4);

//	viewmatrix(2, 3) = -10;
//	modelview(2, 3) = -10;
}

void glTranslationDemo::showmatrix()
{
	while( modelviewmatrixshow->count() > 0) {
		QWidget *widget = modelviewmatrixshow->itemAt(0)->widget();
		modelviewmatrixshow->removeWidget(widget);
		delete widget;

		widget = viewmatrixshow->itemAt(0)->widget();
		viewmatrixshow->removeWidget(widget);
		delete widget;

		widget = modelmatrixshow->itemAt(0)->widget();
		modelmatrixshow->removeWidget(widget);
		delete widget;
	}
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			modelviewmatrixshow->addWidget(new QLabel(QString::number(modelview(i, j))), i, j, 1, 1);
			viewmatrixshow->addWidget(new QLabel(QString::number(viewmatrix(i, j))), i, j, 1, 1);
			modelmatrixshow->addWidget(new QLabel(QString::number(modelmatrix(i, j))), i, j, 1, 1);
		}
	}
}