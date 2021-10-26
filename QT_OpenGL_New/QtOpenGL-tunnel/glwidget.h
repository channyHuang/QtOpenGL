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
    QString m_sProPath;
    QTimer timer;

    QOpenGLShaderProgram *m_shader;
    QOpenGLVertexArrayObject *m_vao;

    QMatrix4x4 projection;

    struct {
        GLint mv_matrix;
        GLint offset;
    } uniforms;

    GLuint tex_wall, tex_ceiling, tex_floor;

    ktxLoader cKtxLoader;
    ObjectLoader objLoader;
    QOpenGLFunctions_4_2_Core *f = nullptr;

    float currentTime = 0;
};

#endif
