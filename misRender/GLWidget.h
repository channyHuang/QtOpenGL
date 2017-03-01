#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QtOpenGL/QGLWidget>
#include <QPaintEvent>
#include <QPixmap>

class GLWidget : public QGLWidget
{
	Q_OBJECT
public:
	GLWidget(QWidget *parent = 0);
	~GLWidget();


protected:
	void initializeGL();
	void resize(int w, int h);
	void paintEvent(QPaintEvent* event);
	void paintGL();

	void init2D();
	void init3D();
	void draw2D();
	void draw3D();

	void DrawCube(double length,
		const QColor topFace,
		const QColor buttomFace,
		const QColor leftFace,
		const QColor rightFace,
		const QColor frontFace,
		const QColor backFace);
	void DrawTetrahedron(double length,
		const QColor sideFace1,
		const QColor sideFace2,
		const QColor sideFace3,
		const QColor buttomFace);

private:
	enum { Cube = 0, Tetrahedron, ListCount };
	GLuint          m_List[ListCount];
	QPixmap         m_Background;

	float           m_Angle;

};

#endif