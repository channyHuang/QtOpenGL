#include "gllightdemo.h"

#include <QVBoxLayout>

#include <iostream>
using namespace std;

glLightDemo::glLightDemo(QWidget *parent)
	:ui(new Ui::glLightDemo), QWidget(parent)
{
	ui->setupUi(this);

	glWidget = new GlWidget(NULL);

	QVBoxLayout *mainlayout = new QVBoxLayout();
	mainlayout->addWidget(glWidget);
	setLayout(mainlayout);
}

glLightDemo::~glLightDemo()
{
	delete ui;
}
/*
void glLightDemo::keyPressEvent(QKeyEvent *e)
{
	switch (e->key())
	{
	case Qt::Key_W:
		g_camera.cam[1] += 0.1;
		break;
	case Qt::Key_S:
		g_camera.cam[1] -= 0.1;
		break;
	case Qt::Key_A:
		g_camera.cam[0] -= 0.1;
		break;
	case Qt::Key_D:
		g_camera.cam[0] += 0.1;
		break;
	case Qt::Key_R:
		g_camera.cam[2] += 0.1;
		break;
	case Qt::Key_F:
		g_camera.cam[2] -= 0.1;
		break;
	case Qt::Key_M:
		gRotatefSpeed_1 += 5.0f;
		break;
	case Qt::Key_N:
		gRotatefSpeed_1 -= 5.0f;
		break;
	case Qt::Key_4:
		isRotatef[3] = true;
		isRotatef[0] = isRotatef[1] = isRotatef[2] = false;
		break;
	case Qt::Key_5:
		g_camera.cam[0] = g_camera.cam[1] = g_camera.cam[2] = 0.0f;
		g_tmpX = 0;
		g_tmpY = 0;
		g_mousePos_y = 0;
		g_mousePos_x = 0;
		g_RotatefY = 0.0f;
		break;
	case Qt::Key_1:
		isRotatef[0] = true;
		isRotatef[1] = isRotatef[2] = isRotatef[3] = false;
		break;
	case Qt::Key_2:
		isRotatef[1] = true;
		isRotatef[0] = isRotatef[2] = isRotatef[3] = false;
		break;
	case Qt::Key_3:
		isRotatef[2] = true;
		isRotatef[0] = isRotatef[1] = isRotatef[3] = false;
		break;
	case Qt::Key_I:
		gLightOpen[0] = !gLightOpen[0];
		if (!gLightOpen[0])
		{
			glDisable(GL_LIGHT0);
		}
		else
		{
			glEnable(GL_LIGHT0);
		}
		break;
	case Qt::Key_O:
		gLightOpen[1] = !gLightOpen[1];
		if (!gLightOpen[1])
		{
			glDisable(GL_LIGHT1);
		}
		else
		{
			glEnable(GL_LIGHT1);
		}
		break;
	case Qt::Key_Y:
		g_RotatefY += 2.0f;
		break;
	case Qt::Key_P:
		gLightOpen[2] = !gLightOpen[2];
		if (!gLightOpen[2])
		{
			glDisable(GL_LIGHT2);
		}
		else
		{
			glEnable(GL_LIGHT2);
		}
		break;
	default:
		break;
	}
	glWidget->updateGL();
}

void glLightDemo::mousePressEvent(QMouseEvent *e)
{
	switch (e->button())
	{
	case Qt::LeftButton:
		if (true) {
			g_tmpX = e->x();
			g_tmpY = e->y();
			g_rotate = true;
		}
		else {
			g_rotate = false;
		}
		break;
	default:
		break;
	}
}
*/