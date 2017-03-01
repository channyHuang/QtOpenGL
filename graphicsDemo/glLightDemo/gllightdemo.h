#ifndef GLLIGHTDEMO_H
#define GLLIGHTDEMO_H

#include <QtWidgets/QWidget>
#include "ui_gllightdemo.h"

#include "glWidget.h"

namespace Ui
{
	class glLightDemo;
}

class glLightDemo : public QWidget
{
	Q_OBJECT

public:
	glLightDemo(QWidget *parent = 0);
	~glLightDemo();

//	void keyPressEvent(QKeyEvent *e);
//	void mousePressEvent(QMouseEvent *e);
private:
	Ui::glLightDemo *ui;
	GlWidget *glWidget;
};

#endif // GLLIGHTDEMO_H
