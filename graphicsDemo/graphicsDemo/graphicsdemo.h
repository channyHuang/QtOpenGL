#ifndef GRAPHICSDEMO_H
#define GRAPHICSDEMO_H

#include <QtWidgets/QWidget>
#include <QKeyEvent>
#include <QMouseEvent>
#include "ui_graphicsdemo.h"

#include "PhongModel.h"
#include "Bezier.h"
#include "BSpine.h"

namespace Ui
{
	class graphicsDemo;
}

class graphicsDemo : public QWidget
{
	Q_OBJECT

public:
	graphicsDemo(QWidget *parent = 0);
	~graphicsDemo();

	void initwidgets();

	void keyPressEvent(QKeyEvent *e);
	void mousePressEvent(QMouseEvent *e);
private:
	Ui::graphicsDemo *ui;

	LightClass *lightclass;
	BezierClass *bezierclass;
	BspineClass *bspineclass;
};

#endif // GRAPHICSDEMO_H
