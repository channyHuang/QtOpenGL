#ifndef WIDGET_H
#define WIDGET_H

#include <QOpenGLWidget>
#include <QTimer>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>

struct VertexData
{
    QVector3D position;
    QVector2D texCoord;
};

class GlWidget : public QOpenGLWidget
{
    Q_OBJECT
public:
    GlWidget(QWidget *partent);
    ~GlWidget();
protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int w, int h) override;

private:
    void initCubeGeometry();
    void drawCubeGeometry();
    void initShader();

private:
    QOpenGLShaderProgram *m_shader;
    QOpenGLVertexArrayObject *m_vao;
    QOpenGLBuffer *arrayBuf, *indexBuf;

    QMatrix4x4 projection;
    QQuaternion rotation;
    QVector3D rotationAxis;
    qreal angularSpeed = 1.f;
    QTimer timer;
};

#endif