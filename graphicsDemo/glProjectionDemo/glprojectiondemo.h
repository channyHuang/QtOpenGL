#ifndef GLPROJECTIONDEMO_H
#define GLPROJECTIONDEMO_H

#include <QtWidgets/QWidget>
#include "ui_glprojectiondemo.h"

#include <QPushButton>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QGroupBox>
#include <QGridLayout>
#include <QRadioButton>

#include "glWindow.h"
#include "glWindow3D.h"

namespace Ui
{
	class glProjectionDemo;
}

class glProjectionDemo : public QWidget
{
	Q_OBJECT

public:
	glProjectionDemo(QWidget *parent = 0);
	~glProjectionDemo();

private slots:
	void reset();
	void computeMatrix();

private:
	Ui::glProjectionDemo *ui;

	void initwidgets();
	void initconnects();

	void showmatrix();
	void drawSpheres();

	glWindow *glwindow;
	glWindow3D *glwindow3d;

	QPushButton *resetbtn;
	QSpinBox *nearbox, *farbox;
	QDoubleSpinBox *leftbox, *rightbox, *bottombox, *topbox;

	QGridLayout *matrixlayout;
	QGroupBox *projmatrixbox;

	QRadioButton *persbtn, *orthobtn;
};

#endif // GLPROJECTIONDEMO_H
