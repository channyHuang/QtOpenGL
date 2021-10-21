#ifndef WIDGET_H
#define WIDGET_H

#include <QOpenGLWidget>
#include <QTimer>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLTexture>

#include "objectloader.h"
#include "ktxloader.h"

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
    void initObjects();
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

    struct {
        GLint mv_matrix;
        GLint proj_matrix;
    } uniforms;

    GLuint tex_object[2];
    GLuint tex_index = 0;

    ktxLoader cKtxLoader;
    ObjectLoader objLoader;
    QOpenGLFunctions_4_2_Core *f = nullptr;
};

#endif
