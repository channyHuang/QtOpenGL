#include "GLWidget.h"

#include <GL/glut.h>

GLWidget::GLWidget(QWidget *parent) :QGLWidget(parent)
{
	init2D();
	init3D();
	m_Angle = 0.0f;

	setAutoFillBackground(false);
	setAutoBufferSwap(false);
//	setWindowTitle("Show 2D and 3D in one widget");
}

GLWidget::~GLWidget() {}

void GLWidget::initializeGL()
{
	glEnable(GL_DEPTH);
	glFrontFace(GL_CW);
	glEnable(GL_CULL_FACE);
	glShadeModel(GL_FLAT);
}

void GLWidget::resize(int w, int h)
{
	if (h == 0) h = 1;
	glViewport(0, 0, (GLint)w, (GLint)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0,                       // 视野角度
		(double)w / (double)h,// 宽高比
		1.0,                        // 近裁面z值
		1000.0);                   // 远裁面z值
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void GLWidget::paintEvent(QPaintEvent* event)
{
	draw2D();
	draw3D();

	swapBuffers();
	update();
}

void GLWidget::paintGL()
{
	update();
}

void GLWidget::init2D()
{
	if (m_Background.load("./Background.jpg"))
	{
		setFixedSize(m_Background.size());
	}
	else
	{
		m_Background.scaled(640, 480);// 如果载入失败，强制让其为长640高480
	}
}

void GLWidget::init3D()
{
	makeCurrent();
	m_List[Cube] = glGenLists(ListCount);
	m_List[Tetrahedron] = m_List[Cube] + 1;
	glNewList(m_List[Cube], GL_COMPILE);
	DrawCube(0.2, Qt::white,
		Qt::yellow,
		Qt::blue,
		Qt::red,
		Qt::green,
		Qt::cyan);
	glEndList();

	glNewList(m_List[Tetrahedron], GL_COMPILE);
	DrawTetrahedron(1.0,
		Qt::yellow,
		Qt::blue,
		Qt::red,
		Qt::green);
	glEndList();
}

void GLWidget::draw2D()
{
	QPainter painter(this);
	painter.drawPixmap(0, 0, m_Background);
}

void GLWidget::draw3D()
{
	const float x = 0.800f,//3.0f / 8.0f * size( ).rwidth( ),
		y = 0.400f;//size( ).rheight( ) / 4.0f;
	
	glLoadIdentity();
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glPushMatrix();
	glTranslatef(-x, y, -0.20f);
	glRotatef(m_Angle, 1.0f, 1.0f, 0.0f);
	glCallList(m_List[Cube]);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(x, y, -0.20f);
	glRotatef(m_Angle, 1.0f, 1.0f, 0.0f);
	glCallList(m_List[Tetrahedron]);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(x, -y, -0.20f);
	glRotatef(m_Angle, 1.0f, 1.0f, 0.0f);
	glCallList(m_List[Cube]);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-x, -y, -200.0f);
	glRotatef(m_Angle, 1.0f, 1.0f, 0.0f);
	glCallList(m_List[Tetrahedron]);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, -y, -0.20f);
	qglColor(Qt::black);
	renderText(-0.50, 0.0, 0.0,                // 字体所在的位置
		tr("Made In China")); // 文本
	glPopMatrix();

	m_Angle += 1.0f;

}

void GLWidget::DrawCube(double length,
	const QColor topFace,
	const QColor buttomFace,
	const QColor leftFace,
	const QColor rightFace,
	const QColor frontFace,
	const QColor backFace)
{
	const double p1[3] = { -length / 2.0, -length / 2.0, length / 2.0 };
	const double p2[3] = { length / 2.0, -length / 2.0, length / 2.0 };
	const double p3[3] = { length / 2.0, -length / 2.0, -length / 2.0 };
	const double p4[3] = { -length / 2.0, -length / 2.0, -length / 2.0 };
	const double p5[3] = { -length / 2.0, length / 2.0, length / 2.0 };
	const double p6[3] = { length / 2.0, length / 2.0, length / 2.0 };
	const double p7[3] = { length / 2.0, length / 2.0, -length / 2.0 };
	const double p8[3] = { -length / 2.0, length / 2.0, -length / 2.0 };

	glBegin(GL_QUADS);

	// 上
	qglColor(topFace);
	glVertex3dv(p8); glVertex3dv(p7);
	glVertex3dv(p6); glVertex3dv(p5);

	// 下
	qglColor(buttomFace);
	glVertex3dv(p1); glVertex3dv(p2);
	glVertex3dv(p3); glVertex3dv(p4);

	// 左
	qglColor(leftFace);
	glVertex3dv(p8); glVertex3dv(p5);
	glVertex3dv(p1); glVertex3dv(p4);

	// 右
	qglColor(rightFace);
	glVertex3dv(p6); glVertex3dv(p7);
	glVertex3dv(p3); glVertex3dv(p2);

	// 前
	qglColor(frontFace);
	glVertex3dv(p5); glVertex3dv(p6);
	glVertex3dv(p2); glVertex3dv(p1);

	// 后
	qglColor(backFace);
	glVertex3dv(p7); glVertex3dv(p8);
	glVertex3dv(p4); glVertex3dv(p3);
	glEnd();
}
/*---------------------------------------------------------------------------*/
void GLWidget::DrawTetrahedron(double length,
	const QColor sideFace1,
	const QColor sideFace2,
	const QColor sideFace3,
	const QColor buttomFace)
{
	const double sqrt2 = 1.414213562;
	const double sqrt6 = 2.449489743;
	const double p1[3] = { 0.0, length, 0.0 };
	const double p2[3] = { -sqrt6 / 3.0 * length, -length / 3.0, sqrt2 / 3.0 * length };
	const double p3[3] = { sqrt6 / 3.0 * length, -length / 3.0, sqrt2 / 3.0 * length };
	const double p4[3] = { 0.0, -length / 3.0, -2 * sqrt2 / 3.0 * length };

	glBegin(GL_TRIANGLES);
	// 侧面一、二、三
	qglColor(sideFace1);
	glVertex3dv(p1); glVertex3dv(p3); glVertex3dv(p2);
	qglColor(sideFace2);
	glVertex3dv(p1); glVertex3dv(p4); glVertex3dv(p3);
	qglColor(sideFace3);
	glVertex3dv(p1); glVertex3dv(p2); glVertex3dv(p4);

	// 底面
	qglColor(buttomFace);
	glVertex3dv(p2); glVertex3dv(p3); glVertex3dv(p4);
	glEnd();
}
