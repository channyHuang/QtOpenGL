#ifndef WIDGET_H
#define WIDGET_H

#include <QOpenGLWidget>
#include <QTimer>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLTexture>
#include <QMouseEvent>

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

    void mousePressEvent(QMouseEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;

private:
    void initCubeGeometry();
    void drawCubeGeometry();
    void initShader();
    void initTexture();

private:
    QOpenGLShaderProgram *m_shader;
    QOpenGLVertexArrayObject *m_vao;
    QOpenGLBuffer *arrayBuf, *indexBuf;

    QMatrix4x4 projection;
    QQuaternion rotation;
    QVector3D rotationAxis;
    qreal angularSpeed;
    QTimer timer;

    QOpenGLTexture *m_texture;

    QVector2D mousePressPosition;

    bool m_core = false;
};

#endif
